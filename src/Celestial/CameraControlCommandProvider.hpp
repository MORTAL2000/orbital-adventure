#pragma once
#include "../CommandProvider.hpp"
#include "../engine/InputListener.hpp"
#include "CelestialCameraManager.hpp"
#include "glm/vec2.hpp"

namespace oa {
namespace game {
class CameraControlCommandProvider : public CommandProvider,
                                     public input::InputListener {
  CelestialCameraManager *cameraMgr;
  glm::quat quaternion;
  glm::quat freeQuat;
  glm::quat currentRotation;
  glm::mat4 cm;
  glm::vec3 cameraDirection;
  glm::vec3 cameraPosition;
  glm::vec3 currentAxis;
  bool rotationInProgress = false;
  bool movementInProgress = false;
  float distance;
  float currentCameraSpeed;
  double lat, lon;
  float dax = 0, day = 0, daz = 0;
  bool lookAtPlanetCenter = false;
  glm::vec3 center;
  glm::vec3 up;

  bool leftButtonPressed = false;

  glm::vec2 lastMousePosition;
  glm::vec2 mousePositionOnLeftButton;

  void onMouseDown(int key, int mods);
  void onMouseUp(int key, int mods);
  void onMouseMove(glm::vec2 point);
  void onScroll(double w, double v);
  void onKeyDown(int keyCode, int mods);
  void onKeyUp(int keyCode, int mods);

  void createCommand();
  void update(float);

 public:
  CameraControlCommandProvider(CommandAcceptor *, CelestialCameraManager *);
};
}
}
