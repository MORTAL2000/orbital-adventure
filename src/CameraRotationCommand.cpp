#include "CameraRotationCommand.hpp"
namespace oa {
namespace game {
CameraRotationCommand::CameraRotationCommand(CelestialCameraManager *c,
                                             glm::vec3 dir, float distance)
    : cameraMgrPtr(c), direction(dir), distance(distance) {}
void CameraRotationCommand::execute() {
  cameraMgrPtr->setRotationAndDistance(direction, distance);
}
}
}
