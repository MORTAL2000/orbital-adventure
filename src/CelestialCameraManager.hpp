#pragma once
#include "memory.h"
#include "SolarSystem.hpp"
#include "engine/Camera.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
namespace oa {
namespace game {
class CelestialCameraManager {
  std::unique_ptr<render::Camera> camera;
  glm::vec3 center;
  glm::vec3 dir;
  glm::vec3 up;
  float distance;

 public:
  CelestialCameraManager();
  void setRotationAndDistance(glm::vec3 r, float d);
  void setCurrentCelestial(const CelestialObject *object);
  void setSolarSystem(SolarSystem *);
  const render::Camera *getCamera();
};
}
}
