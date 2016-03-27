#include "CameraRotationCommand.hpp"
namespace oa {
namespace game {
CameraRotationCommand::CameraRotationCommand(render::Camera *c, glm::quat q)
    : cameraPtr(c), rotation(q) {}
void CameraRotationCommand::execute() { cameraPtr->setRotation(rotation); }
}
}
