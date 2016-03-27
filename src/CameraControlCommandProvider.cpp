#pragma once
#include "CameraControlCommandProvider.hpp"
#include "CameraRotationCommand.hpp"
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
namespace oa {
namespace game {
CameraControlCommandProvider::CameraControlCommandProvider(CommandAcceptor *a,
                                                           render::Camera *c)
    : CommandProvider(a), camera(c), lastQuaternion(1, 0, 0, 0) {}

void CameraControlCommandProvider::onMouseDown(int key, int mod) {
  if (key == 0) {
    leftButtonPressed = true;
    mousePositionOnLeftButton = lastMousePosition;
    lastQuaternion = camera->getRotation();
  }
}

void CameraControlCommandProvider::onMouseUp(int key, int mod) {
  if (key == 0) leftButtonPressed = false;
}

void CameraControlCommandProvider::onMouseMove(glm::vec2 point) {
  lastMousePosition = point;
  if (leftButtonPressed) {
    glm::fvec2 diff = lastMousePosition - mousePositionOnLeftButton;
    auto len = glm::length(diff) / 1000;

    if (len > 0) {
      auto angle = std::atan2(diff.y, diff.x);

      auto prequat = glm::angleAxis(diff.x / 500, glm::vec3(0.0f, -1.0f, 0.0f));
      prequat *= glm::angleAxis(diff.y / 500, glm::vec3(-1.0f, 0.0f, 0.0f));
      std::cout << "lastQuaternion "
                << " x " << prequat.x << " y " << prequat.y << " z "
                << prequat.z << " w " << prequat.w << " DX " << diff.x << "\n";
      addCommand(new CameraRotationCommand(
          camera, glm::normalize(lastQuaternion * prequat)));
    }
  }
}

void CameraControlCommandProvider::onScroll(double w, double v) {
  std::cout << "D: " << w << "/" << v << "\n";
}
}
}
