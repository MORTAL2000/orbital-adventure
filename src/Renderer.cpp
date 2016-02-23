#include "Renderer.hpp"
#include <iostream>
namespace oa {
namespace render {
Renderer::Renderer() {}
void Renderer::render(const render::Camera *const camera) {
  renderSolarSystem(camera);
  renderPlanetarySystem(camera);
}

void Renderer::setSolarSystem(const game::SolarSystem *ss) { solarSystem = ss; }

void Renderer::renderSolarSystem(const render::Camera *const camera) {
  auto celestialCamera = camera->changeClipping(0, 1e10);
  auto projectionView = celestialCamera->getMatrix();
  for (auto &pair : *solarSystem->getCelestialMeshes()) {
    auto mesh = pair.second;
    auto indices = mesh->setupGeometry();
    mesh->setupUniforms(projectionView);
    this->drawElements(indices);
  }
}

void Renderer::renderPlanetarySystem(const render::Camera *const camera) {
  std::cout << "No render today\n";
}

void Renderer::drawElements(uint32_t amount) {
  glDrawElements(GL_TRIANGLES,     // mode
                 amount,           // count
                 GL_UNSIGNED_INT,  // type
                 (void *)0         // element array buffer offset
                 );
}
}
}
