#include "CameraRotationCommand.hpp"
namespace oa {
namespace game {
CameraRotationCommand::CameraRotationCommand(render::Camera *c, glm::vec3 eye,
                                             glm::vec3 center, glm::vec3 up)
    : cameraPtr(c), center(center), eye(eye), up(up) {}
void CameraRotationCommand::execute() { cameraPtr->lookAt(eye, center, up); }
}
}
