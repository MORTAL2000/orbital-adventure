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

void Renderer::render(TextureCreator *textureCreator, UniformHolder *holder) {
  std::vector<std::string> &targets = textureCreator->getTargets();
  auto width = textureCreator->supposedWidth();
  auto height = textureCreator->supposedHeight();
  auto depth = textureCreator->supposedDepth();
  if (framebuffer == 0) createFrameBuffer(true);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  if (textureCreator->needsDepthTest()) {
    if (!depthbuffer) glGenRenderbuffers(1, &depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, depthbuffer);
  } else {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, 0);
  }

  GLenum buffers[targets.size()];
  GLuint textures[targets.size()];
  int ix = 0;
  for (auto target : targets) {
    glGenTextures(targets.size(), textures);
    if (depth == 1) {
      glBindTexture(GL_TEXTURE_2D, textures[ix]);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA,
                   GL_FLOAT, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      holder->setUniformValue(targets[ix],
                              new TextureOwnerUniform(textures[ix]));
    } else {
      std::cout << "3d tex " << width << "x" << height << "x" << depth << "\n";
      glBindTexture(GL_TEXTURE_3D, textures[ix]);
      glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32F, width, height, depth, 0,
                   GL_RGBA, GL_FLOAT, 0);
      glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      holder->setUniformValue(targets[ix],
                              new Texture3DOwnerUniform(textures[ix]));
    }

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + ix,
                         textures[ix], 0);
    buffers[ix] = GL_COLOR_ATTACHMENT0 + ix;
    ++ix;
  }
  glDrawBuffers(targets.size(), buffers);
  auto res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (res != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Was unable to setup framebuffer with target " << targets[0]
              << "\n";
    std::cerr << std::hex << "RESULT " << res << "\n";
    std::cerr << std::dec;
    return;
  }
  glViewport(0, 0, width, height);
  glClearColor(0.0, 1.0, 1.0, 1.0);
  glDisable(GL_DEPTH_TEST);
  textureCreator->render();

  for (int ix = 0; ix < targets.size(); ++ix)
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + ix, 0, 0);

  std::cout << "___________unbind____________\n";
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glEnable(GL_DEPTH_TEST);
}

void Renderer::createFrameBuffer(bool needsDepth) {
  glGenFramebuffers(1, &framebuffer);
}
void Renderer::renderSorted(const Scene *scene, const Camera *camera) {
  GLuint currentProgram = 0;

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
}

void Renderer::render(const Scene *scene, const Camera *camera) {
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
}
}
}
