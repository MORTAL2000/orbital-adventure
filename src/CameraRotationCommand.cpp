#include "CameraRotationCommand.hpp"
namespace oa {
namespace game {
CameraRotationCommand::CameraRotationCommand(CelestialCameraManager *c,
                                             glm::vec3 pd, glm::vec3 cd,
                                             float distance)
    : cameraMgrPtr(c), posDir(pd), camDir(cd), distance(distance) {}
void CameraRotationCommand::execute() {
  cameraMgrPtr->setRotationAndDistance(camDir, posDir, distance);
}
}
}
