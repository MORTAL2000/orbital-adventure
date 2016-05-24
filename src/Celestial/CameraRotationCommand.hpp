#pragma once
#include "../Command.hpp"
#include "CelestialCameraManager.hpp"
namespace oa {
namespace game {
class CameraRotationCommand : public Command {
  glm::vec3 posDir;
  glm::vec3 camDir;
  glm::vec3 up;
  CelestialCameraManager *cameraMgrPtr;
  void execute();

 public:
  CameraRotationCommand(CelestialCameraManager *, glm::vec3 position,
                        glm::vec3 camDir, glm::vec3 up);
};
}
}
