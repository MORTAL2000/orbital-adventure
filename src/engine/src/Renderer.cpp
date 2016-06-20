#include "Renderer.hpp"
#include <iostream>
#include "LanguageUtils.hpp"
#include "Uniform.hpp"
namespace oa {
namespace render {
using namespace utils;
Renderer::Renderer() : framebuffer(0), depthbuffer(0), VertexArrayID(0) {}

void Renderer::clearColor() { glClear(GL_COLOR_BUFFER_BIT); }
void Renderer::clearDepth() { glClear(GL_DEPTH_BUFFER_BIT); }
void Renderer::resetRenderState() {
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
}

void Renderer::startFBORendering() {
  if (filters.size() > 0) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    bindTargets({mainTarget});
  } else {
    unbindFramebuffer();
  }
}

void Renderer::bindVertexArrayBuffer() {
  if (VertexArrayID == 0) glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
}

void Renderer::unbindTargets() {
  for (size_t i = 0; i < lastTargetsAmount; ++i) {
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, 0, 0);
  }
}

Renderer::RenderTargetsUniformInstaller::RenderTargetsUniformInstaller(
    std::map<std::string, GLuint> *m, bool *tu, int *w, int *h)
    : map(m), texturesUpdated(tu), width(w), height(h) {}

void Renderer::RenderTargetsUniformInstaller::install(UniformHolder *holder,
                                                      const Camera *, double) {
  if (*texturesUpdated) {
    for (auto &pair : *map) {
      holder->setUniformValue(pair.first, new TextureUniform(pair.second));
    }
    glm::ivec2 res(*width, *height);
    holder->setUniformValue("viewportResolution", new IntVec2OwnerUniform(res));
  }
}

void Renderer::renderFilters() {
  geometry::Geometry *currentGeometry = nullptr;
  GLuint currentProgram;
  for (size_t i = 0; i < filters.size(); ++i) {
    bool isLast = i == (filters.size() - 1);
    auto &f = filters[i];
    if (!isLast) {
      bindTargets(f->getTargets());
    } else {
      unbindFramebuffer();
    }
    f->setupRenderingMode();
    GLuint program = f->getProgramId();
    if (program != currentProgram) {
      currentProgram = program;
      glUseProgram(currentProgram);
    }
    auto geometry = f->getGeometry();
    if (geometry != currentGeometry) {
      if (currentGeometry) currentGeometry->unsetBuffers();
      currentGeometry = geometry;
      currentGeometry->setBuffers();
    }
    f->updateUniforms();
    glDisable(GL_DEPTH_TEST);
    currentGeometry->render();
    glEnable(GL_DEPTH_TEST);
    unbindTargets();
  }
}

void Renderer::unbindFramebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
void Renderer::bindTarget(const std::string &target) {
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  GLuint texture;
  GLuint buffers[1];
  if (targets.count(target) == 0) {
    std::cout << "ERROR: " << target << " No such texture\n";
    return;
  }
  texture = targets[target];
  buffers[0] = GL_COLOR_ATTACHMENT0;
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
  lastTargetsAmount = 1;
  glDrawBuffers(1, buffers);
}

void Renderer::bindTargets(std::vector<std::string> &ts) {
  GLuint textures[ts.size()];
  GLuint buffers[ts.size()];
  for (size_t i = 0; i < ts.size(); ++i) {
    textures[i] = targets[ts[i]];
    buffers[i] = GL_COLOR_ATTACHMENT0 + i;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, textures[i],
                         0);
  }
  lastTargetsAmount = ts.size();
  glDrawBuffers(ts.size(), buffers);
}
void Renderer::bindTargets(std::vector<std::string> &&ts) {
  GLuint textures[ts.size()];
  GLuint buffers[ts.size()];
  for (size_t i = 0; i < ts.size(); ++i) {
    textures[i] = targets[ts[i]];
    buffers[i] = GL_COLOR_ATTACHMENT0 + i;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, textures[i],
                         0);
  }
  glDrawBuffers(ts.size(), buffers);
}

void Renderer::initFBOTargets(Filter *f) {
  if (!framebuffer) glGenFramebuffers(1, &framebuffer);
  for (std::string &target : f->getTargets()) {
    if (!targets.count(target)) setupTarget(target, 4);
  }
}

void Renderer::setupTarget(const std::string &name, int componentSize) {
  if (targets.count(name) > 0) glDeleteTextures(1, &targets[name]);
  int type;
  if (componentSize == 1) type = GL_RGBA;
  if (componentSize == 2) type = GL_RGBA16F;
  if (componentSize == 4) type = GL_RGBA32F;
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, GL_RGBA, GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  targets[name] = texture;
  updateUniformHolder();
}

void Renderer::render(TextureCreator *textureCreator, UniformHolder *holder) {
  bindVertexArrayBuffer();
  resetRenderState();
  // holder is the source of uniforms and destinations of them at the same
  // time;
  if (!framebuffer) glGenFramebuffers(1, &framebuffer);
  textureCreator->prepareFramebuffer(framebuffer, holder);
  textureCreator->render(holder);
  textureCreator->cleanFramebuffer(framebuffer);
  glDeleteFramebuffers(1, &framebuffer);
  framebuffer = 0;
}

void Renderer::createFrameBuffer(bool needsDepth) {
  glGenFramebuffers(1, &framebuffer);
}

void Renderer::renderSorted(const Scene *scene, const Camera *camera) {
  GLuint currentProgram = 0;

  bindVertexArrayBuffer();
  resetRenderState();
  startFBORendering();

  geometry::Geometry *currentGeometry = nullptr;
  for (auto m : scene->getSortedMeshes(camera->getPosition())) {
    clearDepth();
    GLuint program = m->getProgramId();
    if (program != currentProgram) {
      currentProgram = program;
      glUseProgram(currentProgram);
    }
    auto geometry = m->getGeometry();
    if (geometry != currentGeometry) {
      if (currentGeometry) currentGeometry->unsetBuffers();
      currentGeometry = geometry;
      currentGeometry->setBuffers();
    }
    m->setupUniforms(camera, scene, 0.0);
    currentGeometry->render();
  }

  renderFilters();
}

void Renderer::pushFilter(Filter *f) {
  f->addUniformInstaller(new RenderTargetsUniformInstaller(
      &targets, &texturesUpdated, &width, &height));
  filters.push_back(std::unique_ptr<Filter>(f));

  reinitFBOTargetTextures();
}

void Renderer::updateUniformHolder() {
  texturesUpdated = true;
  for (auto &f : filters) {
    f->updateUniforms();
  }
  texturesUpdated = false;
}
void Renderer::reinitFBOTargetTextures() {
  for (auto &t : targets) {
    glDeleteTextures(1, &t.second);
  }
  targets.clear();
  setupTarget(mainTarget, 1);
  for (auto &f : filters) {
    initFBOTargets(f.get());
  }
  updateUniformHolder();
}

void Renderer::setViewportDimentions(int width, int height) {
  this->width = width;
  this->height = height;
  reinitFBOTargetTextures();
  glViewport(0, 0, width, height);
}
void Renderer::render(const Scene *scene, const Camera *camera) {
  bindVertexArrayBuffer();
  resetRenderState();
  startFBORendering();
  for (auto sp : scene->getAllShaders()) {
    glUseProgram(sp->getProgramId());
    for (auto g : scene->getGeometries(sp)) {
      g->setBuffers();
      for (auto m : scene->getMeshes(g)) {
        m->prerender(scene);
        m->setupUniforms(camera, scene, 0.0);
        g->render();
      }
      g->unsetBuffers();
    }
  }
  renderFilters();
}
}
}
