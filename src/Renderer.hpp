#pragma once
#include "GLFWWrapper.hpp"
#include "PlanetID.hpp"
#include "SolarSystem.hpp"
#include "Camera.hpp"
namespace oa {
namespace render {
class Renderer {
 private:
  game::SolarSystem const* solarSystem;
  void renderSolarSystem(const render::Camera* const);
  void renderPlanetarySystem(const render::Camera* const);
  void drawElements(uint32_t);

 public:
  Renderer();
  void setSolarSystem(const game::SolarSystem* const);
  void setPlanetaryMeshes();
  void setActivePlanet(game::PlanetID);
  void render(const Camera* const);
};
}
}
