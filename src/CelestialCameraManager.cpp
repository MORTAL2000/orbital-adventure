#include <iostream>
#include "CelestialCameraManager.hpp"
#include "engine/PerspectiveCamera.hpp"
namespace oa {
namespace game {
CelestialCameraManager::CelestialCameraManager()
    : center(0.0, 0.0, 0.0), up(0.0, 0.0, 1.0) {}
const render::Camera* CelestialCameraManager::getCamera() {
  return camera.get();
}

void CelestialCameraManager::setCurrentCelestial(
    const CelestialObject* celestial) {
  center = celestial->getPosition();
  glm::vec3 zero(0.0, 0.0, 0.0);
  camera->lookAt((dir * distance), zero, up);
  solarSystem->setCurrentCelestial(celestial);
}

void CelestialCameraManager::setSolarSystem(SolarSystem* ss) {
  solarSystem = ss;
  double maxClipping = 7e7;
  camera = std::unique_ptr<render::Camera>(new render::PerspectiveCamera(
      glm::radians(45.0f), 4.0f / 3.0f, 2.0e3f, maxClipping * 2 * 10));
}
const CelestialObject* CelestialCameraManager::getCurrentCelestial() {
  return solarSystem->getObjectOfInterest();
}
void CelestialCameraManager::setRotationAndDistance(glm::vec3 dir,
                                                    float distance) {
  this->dir = dir, this->distance = distance;
  glm::vec3 zero(0.0, 0.0, 0.0);
  camera->lookAt((dir * distance), zero, up);
}
}
}
