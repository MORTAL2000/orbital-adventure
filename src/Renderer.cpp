#include <iostream>
#include "Renderer.hpp"
namespace oa {
namespace render {
Renderer::Renderer() {}
void Renderer::render(const render::Camera *const camera) {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  renderSolarSystem(camera);
  renderPlanetarySystem(camera);
}

void Renderer::setSolarSystem(const game::SolarSystem *ss) { solarSystem = ss; }

void Renderer::renderSolarSystem(const render::Camera *const camera) {
  auto celestialCamera = camera;  // ->changeClipping(0, 1000);
  glm::mat4 cameraViewMatrix = celestialCamera->getMatrix();
  glm::mat4 cameraProjection = celestialCamera->getProjectionMatrix();
  for (auto &pair : *solarSystem->getCelestialMeshes()) {
    auto mesh = pair.second;
    glUseProgram(mesh->getProgramId());
    mesh->setupUniforms(cameraProjection, cameraViewMatrix);
    mesh->render();
  }
}

void Renderer::renderPlanetarySystem(const render::Camera *const camera) {
  // std::cout << "No render today\n";
}

void Renderer::drawElements(uint32_t amount) {
  // glDrawElements(GL_TRIANGLES,     // mode
  // amount,           // count
  // GL_UNSIGNED_INT,  // type
  //(void *)0         // element array buffer offset
  //);
}
}
}
