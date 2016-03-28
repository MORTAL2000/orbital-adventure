#pragma once
#include "Command.hpp"
#include "Camera.hpp"
namespace oa {
namespace game {
class CameraRotationCommand : public Command {
  glm::vec3 center, eye, up;
  render::Camera *cameraPtr;
  void execute();

 public:
  CameraRotationCommand(render::Camera *, glm::vec3, glm::vec3, glm::vec3);
};
}
}
