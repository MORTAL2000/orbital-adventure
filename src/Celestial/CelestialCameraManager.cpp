#include <iostream>
#include "CelestialCameraManager.hpp"
#include "LanguageUtils.hpp"
#include "PerspectiveCamera.hpp"
namespace oa {
namespace game {
using namespace utils;
CelestialCameraManager::CelestialCameraManager()
    : center(0.0, 0.0, 0.0), up(0.0, 0.0, 1.0) {}

const render::Camera* CelestialCameraManager::getCamera() const {
  return camera.get();
}

const render::Camera* CelestialCameraManager::getCamera() {
  return camera.get();
}

void CelestialCameraManager::setNewWindowDimensions(int w, int h) {
  double maxClipping = 7e7;
  camera = std::unique_ptr<render::Camera>(new render::PerspectiveCamera(
      glm::radians(45.0f), float(w) / float(h), 2.0e3f, maxClipping * 2 * 10));

  auto d = glm::length(position);
  camera->lookAt(position, position + d * cameraDirection, up);
}

void CelestialCameraManager::setCurrentCelestial(
    const CelestialObject* celestial) {
  auto d = glm::length(position);
  camera->lookAt(position, position + d * cameraDirection, up);
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

void CelestialCameraManager::setRotationAndDistance(glm::vec3 cameraDir,
                                                    glm::vec3 position,
                                                    glm::vec3 upDir) {
  this->position = position;
  distance = glm::length(position);
  cameraDirection = cameraDir;
  up = upDir;
  camera->lookAt(position, position + distance * cameraDirection, up);
}
}
}
