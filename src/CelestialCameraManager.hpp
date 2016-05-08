#pragma once
#include "SolarSystem.hpp"
#include "engine/Camera.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/vec3.hpp"
#include "memory.h"
namespace oa {
namespace game {

class CelestialCameraManager {
  std::unique_ptr<render::Camera> camera;
  SolarSystem *solarSystem;
  glm::vec3 center;
  glm::vec3 position;
  glm::vec3 cameraDirection;
  glm::vec3 up;
  float distance;

 public:
  CelestialCameraManager();
  void setNewWindowDimensions(int width, int height);
  void setRotationAndDistance(glm::vec3 r, glm::vec3, glm::vec3 up);
  void setCurrentCelestial(const CelestialObject *object);
  const CelestialObject *getCurrentCelestial();
  void setSolarSystem(SolarSystem *);
  const render::Camera *getCamera();
  const render::Camera *getCamera() const;
};
}
}
