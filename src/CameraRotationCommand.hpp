#pragma once
#include "Command.hpp"
#include "CelestialCameraManager.hpp"
namespace oa {
namespace game {
class CameraRotationCommand : public Command {
  glm::vec3 direction;
  float distance;
  CelestialCameraManager *cameraMgrPtr;
  void execute();

 public:
  CameraRotationCommand(CelestialCameraManager *, glm::vec3 direction,
                        float distance);
};
}
}
