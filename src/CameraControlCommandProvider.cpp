#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include "CameraControlCommandProvider.hpp"
#include "CameraRotationCommand.hpp"
#include "engine/LanguageUtils.hpp"
namespace oa {
namespace game {
using namespace utils;
CameraControlCommandProvider::CameraControlCommandProvider(
    CommandAcceptor *a, CelestialCameraManager *c)
    : CommandProvider(a),
      cameraMgr(c),
      quaternion(1.0f, 0.f, 0.f, 0.f),
      currentRotation(1.0f, 0.f, 0.f, 0.f),
      distance(1.1 * c->getCurrentCelestial()->getSize()),
      lat(0.5_pi),
      lon(0),
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
  // auto direction =
  //((currentRotation * quaternion) * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
  // glm::vec3 dir3(direction.x, direction.y, direction.z);
  glm::vec3 direction;
  auto l = glm::clamp(lat, 0.0, double(1_pi));
  auto b = std::fmod(lon, double(2_pi));
  std::cout << "Lat" << l << " lon " << b << "\n";
  direction.x = std::sin(l) * std::cos(b);
  direction.y = std::sin(l) * std::sin(b);
  direction.z = std::cos(l);
  std::cout << "dir " << direction << "\n";

  addCommand(new CameraRotationCommand(cameraMgr, direction, distance));
}

void CameraControlCommandProvider::onMouseMove(glm::vec2 point) {
  lastMousePosition = point;
  if (leftButtonPressed) {
    glm::fvec2 diff = lastMousePosition - mousePositionOnLeftButton;
    auto len = glm::length(diff);

    if (len > 0) {
      double dlat = double(diff.y / 500.0);
      double dlon = double(diff.x / 500.0);
      mousePositionOnLeftButton = point;

      lat = glm::clamp(lat - dlat, 0.00001, double(1_pi - 0.0001));
      lon = lon + dlon;

      // currentRotation = glm::quat(1.0, 0, 0, 0);
      // currentRotation =
      // currentRotation *
      // glm::angleAxis(diff.y / 100, glm::vec3(-1.0f, 0.0f, 0.0f));
      // currentRotation =
      // currentRotation *
      // glm::angleAxis(diff.x / 100, glm::vec3(0.0f, -1.0f, 0.0f));

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
