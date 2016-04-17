#include "CelestialCameraManager.hpp"
#include "engine/PerspectiveCamera.hpp"
namespace oa {
namespace game {
CelestialCameraManager::CelestialCameraManager()
    : camera(new render::PerspectiveCamera(glm::radians(45.0f), 4.0f / 3.0f,
                                           1.0f, 100.0f)),
      center(0.0, 0.0, 0.0),
      up(0.0, 1.0, 0.0) {}
const render::Camera* CelestialCameraManager::getCamera() {
  return camera.get();
}

void CelestialCameraManager::setCurrentCelestial(
    const CelestialObject* celestial) {
  center = celestial->getPosition();
  camera->lookAt((dir * distance) + center, center, up);
}
void CelestialCameraManager::setRotationAndDistance(glm::vec3 dir,
                                                    float distance) {
  this->dir = dir, this->distance = distance;
  camera->lookAt((dir * distance) + center, center, up);
}
}
}
