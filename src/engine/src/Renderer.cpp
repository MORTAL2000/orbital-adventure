#include <iostream>
#include "Renderer.hpp"
namespace oa {
namespace render {
Renderer::Renderer() {}

void Renderer::render(const Scene *scene, const Camera *camera) {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  std::cout << "--------------------start ----------------------- \n";
  for (auto sp : scene->getAllShaders()) {
    glUseProgram(sp->getProgramId());
    std::cout << "------------- program-------------------- \n";
    for (auto g : scene->getGeometries(sp)) {
      std::cout << "------------- geometry-------------------- \n";
      g->setBuffers();
      for (auto m : scene->getMeshes(g)) {
        std::cout << "------------- mesh-------------------- \n";

        m->setupUniforms(camera->getProjectionMatrix(), camera->getMatrix());
        g->render();
        std::cout << "------------- mesh end-------------------- \n";
      }
      g->unsetBuffers();
      std::cout << "------------- geometry end-------------------- \n";
    }
    std::cout << "------------- program end-------------------- \n";
  }
  std::cout << "--------------------end ----------------------- \n";
}
}
}
