#pragma once
#include "CameraControlCommandProvider.hpp"
#include "CameraRotationCommand.hpp"
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
namespace oa {
namespace game {
CameraControlCommandProvider::CameraControlCommandProvider(CommandAcceptor *a,
                                                           render::Camera *c)
    : CommandProvider(a),
      camera(c),
      quaternion(1.0f, 0.f, 0.f, 0.f),
      currentRotation(1.0f, 0.f, 0.f, 0.f),
      distance(10.0f),
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
  quaternion = quaternion * currentRotation;
}

void CameraControlCommandProvider::createCommand() {
  auto direction =
      (quaternion * currentRotation * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) *
      distance;
  glm::vec3 dir3(direction.x, direction.y, direction.z);

  addCommand(new CameraRotationCommand(camera, center + dir3, center, up));
}
void CameraControlCommandProvider::onMouseMove(glm::vec2 point) {
  lastMousePosition = point;
  if (leftButtonPressed) {
    glm::fvec2 diff = lastMousePosition - mousePositionOnLeftButton;
    auto len = glm::length(diff);

    if (len > 0) {
      currentRotation =
          glm::angleAxis(diff.x / 100, glm::vec3(0.0f, -1.0f, 0.0f));
      currentRotation *=
          glm::angleAxis(diff.y / 100, glm::vec3(-1.0f, 0.0f, 0.0f));
      std::cout << "lastQuaternion "
                << " x " << currentRotation.x << " y " << currentRotation.y
                << " z " << currentRotation.z << " w " << currentRotation.w
                << " DX " << diff.x << "\n";
      createCommand();
    }
  }
}

void CameraControlCommandProvider::onScroll(double w, double v) {
  distance += v / 100;
  std::cout << "D: " << distance << "\n";
  createCommand();
}
}
}
