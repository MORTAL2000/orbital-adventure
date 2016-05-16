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
  // holder is the source of uniforms and destinations of them at the same time;
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
