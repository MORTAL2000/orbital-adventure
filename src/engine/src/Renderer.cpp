#include <iostream>
#include "LanguageUtils.hpp"
#include "Renderer.hpp"
#include "Uniform.hpp"
namespace oa {
namespace render {
using namespace utils;
Renderer::Renderer() : framebuffer(0), depthbuffer(0) {}

void Renderer::clearColor() { glClear(GL_COLOR_BUFFER_BIT); }
void Renderer::clearDepth() { glClear(GL_DEPTH_BUFFER_BIT); }

void Renderer::startFBORendering() {
  if (filters.size() > 0) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    bindTargets({mainTarget});
  } else {
    unbindFramebuffer();
  }
}

void Renderer::unbindTargets(int amount) {
  for (size_t i = 0; i < amount; ++i) {
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
    currentGeometry->render();
    unbindTargets(f->getTargets().size());
  }
}

void Renderer::unbindFramebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
void Renderer::bindTargets(std::vector<std::string> &ts) {
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
    if (!targets.count(target)) setupTarget(target);
  }
  if (filters.size() > 0 && targets.count(mainTarget) > 0) {
    std::cout << "SETUP MAIN!\n";
    setupTarget(mainTarget);
  }
}

void Renderer::setupTarget(std::string &name) {
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA,
               GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  targets[name] = texture;
}

void Renderer::render(TextureCreator *textureCreator, UniformHolder *holder) {
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

void Renderer::reinitFBOTargetTextures() {
  for (auto &t : targets) {
    glDeleteTextures(1, &t.second);
  }
  for (auto &f : filters) {
    initFBOTargets(f.get());
  }
  texturesUpdated = true;
  for (auto &f : filters) {
    f->updateUniforms();
  }
  texturesUpdated = false;
}

void Renderer::setViewportDimentions(int width, int height) {
  this->width = width;
  this->height = height;
  reinitFBOTargetTextures();
  glViewport(0, 0, width, height);
}
void Renderer::render(const Scene *scene, const Camera *camera) {
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
