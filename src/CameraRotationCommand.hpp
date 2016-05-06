#pragma once
#include "CelestialCameraManager.hpp"
#include "Command.hpp"
namespace oa {
namespace game {
class CameraRotationCommand : public Command {
  glm::vec3 posDir;
  glm::vec3 camDir;
  float distance;
  CelestialCameraManager *cameraMgrPtr;
  void execute();

 public:
  CameraRotationCommand(CelestialCameraManager *, glm::vec3 posDir,
                        glm::vec3 camDir, float distance);
};
}
}
