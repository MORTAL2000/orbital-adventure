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
  std::string name = textureCreator->getTarget();
  auto width = textureCreator->supposedWidth();
  auto height = textureCreator->supposedHeight();
  if (framebuffer == 0) createFrameBuffer(true);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F_ARB, width, height, 0, GL_RGB,
               GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
  GLenum buffers[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, buffers);
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Was unable to setup framebuffer with target" << name << "\n";
    return;
  }
  glViewport(0, 0, width, height);
  textureCreator->render();
  holder->setUniformValue(name, new TextureOwnerUniform(texture));
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
