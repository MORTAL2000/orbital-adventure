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
      freeQuat(-0.55103671550750732, 0.43436530232429504, 0.10900701582431793,
               0.43436530232429504),
      currentRotation(1.0f, 0.f, 0.f, 0.f),
      cameraPosition(2068155.5, 4503610.5, 4025204.25),
      cameraDirection(1.0f, 0.0f, 0.0f),
      currentCameraSpeed(0.0),
      distance(2.1 * c->getCurrentCelestial()->getSize()),
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

void CameraControlCommandProvider::onKeyDown(int keyCode, int mod) {
  std::cout << "key down  " << keyCode << "\n";
  switch (keyCode) {
    case 66:
      currentCameraSpeed *= -1;
      break;
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
      currentCameraSpeed = std::pow(10, keyCode - 49);
      std::cout << "current camera speed " << currentCameraSpeed << "\n";
      break;
    case 32: {
      movementInProgress = true;
      break;
    }
    case 67: {  // c
      currentAxis = glm::vec3(1., 0.0, .0);
      rotationInProgress = true;
      break;
    }
    case 90: {  // z
      currentAxis = glm::vec3(-1., 0.0, .0);
      rotationInProgress = true;
      break;
    }
    case 264: {
      currentAxis = glm::vec3(.0, 1.0, .0);
      rotationInProgress = true;
      break;
    }
    case 265: {
      currentAxis = glm::vec3(.0, -1.0, .0);
      rotationInProgress = true;
      break;
    }
    case 263: {
      currentAxis = glm::vec3(.0, 0.0, 1.0);
      rotationInProgress = true;
      break;
    }
    case 262: {
      currentAxis = glm::vec3(.0, 0.0, -1.0);
      rotationInProgress = true;
      break;
    }
    case 76: {
      lookAtPlanetCenter = !lookAtPlanetCenter;
      createCommand();
      return;
    }
  }
}

void CameraControlCommandProvider::update(float dt) {
  if (movementInProgress) {
    cameraPosition +=
        freeQuat * glm::vec3(1.0, 0.0, 0.0) * dt * currentCameraSpeed;

    createCommand();
  }
  if (rotationInProgress) {
    freeQuat =
        glm::angleAxis(1.0f * dt, glm::normalize(freeQuat * currentAxis)) *
        glm::normalize(freeQuat);
    createCommand();
  }
}

void CameraControlCommandProvider::onKeyUp(int keyCode, int mod) {
  switch (keyCode) {
    case 32:
      movementInProgress = false;
    case 90:
    case 264:
    case 265:
    case 263:
    case 262:
    case 67:
      rotationInProgress = false;
      break;
  }
}

void CameraControlCommandProvider::onMouseUp(int key, int mod) {
  if (key == 0) leftButtonPressed = false;
  quaternion = currentRotation * quaternion;
  currentRotation = glm::quat(1.0, 0, 0, 0);
}

void CameraControlCommandProvider::createCommand() {
  glm::vec3 direction;
  auto l = glm::clamp(lat, 0.0, double(1_pi));
  auto b = std::fmod(lon, double(2_pi));
  direction.x = std::sin(l) * std::cos(b);
  direction.y = std::sin(l) * std::sin(b);
  direction.z = std::cos(l);

  glm::vec3 cd;
  glm::vec3 up(0.0, 0.0, 1.0);
  if (lookAtPlanetCenter) {
    cd = -direction;
    cameraPosition = direction * distance;
  } else {
    cd = glm::vec3(freeQuat * glm::vec4(1.0, 0.0, 0.0, 0.0));
    up = glm::vec3(freeQuat * glm::vec4(up, 0.0));
    std::cout << "POSITION " << cameraPosition << " | " << freeQuat << "\n";
  }
  addCommand(new CameraRotationCommand(cameraMgr, cameraPosition, cd, up));
}

void CameraControlCommandProvider::onMouseMove(glm::vec2 point) {
  float size = cameraMgr->getCurrentCelestial()->getSize();
  float distanceToSurface = distance - size;
  lastMousePosition = point;
  if (leftButtonPressed) {
    glm::fvec2 diff = lastMousePosition - mousePositionOnLeftButton;
    auto len = glm::length(diff);

    if (len > 0) {
      double dlat = double(diff.y * distanceToSurface / 1e10);
      double dlon = double(-diff.x * distanceToSurface / 1e10);
      mousePositionOnLeftButton = point;

      lat = glm::clamp(lat - dlat, 0.00001, double(1_pi - 0.0001));
      lon = lon + dlon;

      createCommand();
    }
  }
}

void CameraControlCommandProvider::onScroll(double w, double v) {
  float size = cameraMgr->getCurrentCelestial()->getSize();
  float distanceToSurface = distance - size;
  float delta = v * std::max(0.5, 0.01 * distanceToSurface);

  distance += delta;
  createCommand();
}
}
}
