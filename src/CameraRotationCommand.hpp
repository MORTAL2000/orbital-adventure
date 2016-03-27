#pragma once
#include "Command.hpp"
#include "Camera.hpp"
namespace oa {
namespace game {
class CameraRotationCommand : public Command {
  glm::quat rotation;
  render::Camera *cameraPtr;
  void execute();

 public:
  CameraRotationCommand(render::Camera *, glm::quat);
};
}
}
