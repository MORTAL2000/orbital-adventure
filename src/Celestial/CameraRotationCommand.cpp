#include "CameraRotationCommand.hpp"
namespace oa {
namespace game {
CameraRotationCommand::CameraRotationCommand(CelestialCameraManager *c,
                                             glm::vec3 pd, glm::vec3 cd,
                                             glm::vec3 up)
    : posDir(pd), camDir(cd), up(up), cameraMgrPtr(c) {}
void CameraRotationCommand::execute() {
  cameraMgrPtr->setRotationAndDistance(camDir, posDir, up);
}
}
}
