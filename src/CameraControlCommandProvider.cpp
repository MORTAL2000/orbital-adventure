#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include "CameraControlCommandProvider.hpp"
#include "CameraRotationCommand.hpp"
namespace oa {
namespace game {
CameraControlCommandProvider::CameraControlCommandProvider(
    CommandAcceptor *a, CelestialCameraManager *c)
    : CommandProvider(a),
      cameraMgr(c),
      quaternion(1.0f, 0.f, 0.f, 0.f),
      currentRotation(1.0f, 0.f, 0.f, 0.f),
      distance(1.1 * c->getCurrentCelestial()->getSize()),
      center(0.0f, 0.0f, 0.0f),
      up(0.0, 1.0f, 0.0f) {
  createCommand();
}

void CameraControlCommandProvider::onMouseDown(int key, int mod) {
  if (key == 0) {
    leftButtonPressed = true;
    mousePositionOnLeftButton = lastMousePosition;
  }
}

void CameraControlCommandProvider::onMouseUp(int key, int mod) {
  if (key == 0) leftButtonPressed = false;
  quaternion = currentRotation * quaternion;
  currentRotation = glm::quat(1.0, 0, 0, 0);
}

void CameraControlCommandProvider::createCommand() {
  auto direction =
      ((currentRotation * quaternion) * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
  glm::vec3 dir3(direction.x, direction.y, direction.z);

  addCommand(new CameraRotationCommand(cameraMgr, dir3, distance));
}

void CameraControlCommandProvider::onMouseMove(glm::vec2 point) {
  lastMousePosition = point;
  if (leftButtonPressed) {
    glm::fvec2 diff = lastMousePosition - mousePositionOnLeftButton;
    auto len = glm::length(diff);

    if (len > 0) {
      currentRotation = glm::quat(1.0, 0, 0, 0);
      currentRotation =
          currentRotation *
          glm::angleAxis(diff.y / 100, glm::vec3(-1.0f, 0.0f, 0.0f));
      currentRotation =
          currentRotation *
          glm::angleAxis(diff.x / 100, glm::vec3(0.0f, -1.0f, 0.0f));

      createCommand();
    }
  }
}

void CameraControlCommandProvider::onScroll(double w, double v) {
  std::cout << "DD " << distance << "\n";
  distance += v * 0.01 * distance;
  createCommand();
}
}
}
