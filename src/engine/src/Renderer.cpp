#include <iostream>
#include "Renderer.hpp"
namespace oa {
namespace render {
Renderer::Renderer() {}

void Renderer::clearColor() { glClear(GL_COLOR_BUFFER_BIT); }
void Renderer::clearDepth() { glClear(GL_DEPTH_BUFFER_BIT); }
void Renderer::render(const Scene *scene, const Camera *camera) {
  for (auto sp : scene->getAllShaders()) {
    glUseProgram(sp->getProgramId());
    for (auto g : scene->getGeometries(sp)) {
      g->setBuffers();
      for (auto m : scene->getMeshes(g)) {
        m->prerender(scene);
        m->setupUniforms(camera, 0.0);
        g->render();
      }
      g->unsetBuffers();
    }
  }
}
}
}
