#pragma once
#include "CommandProvider.hpp"
#include "InputListener.hpp"
#include "Camera.hpp"
#include "glm/vec2.hpp"

namespace oa {
namespace game {
class CameraControlCommandProvider : public CommandProvider,
                                     public input::InputListener {
  render::Camera *camera;
  glm::quat quaternion;
  glm::quat currentRotation;
  glm::mat4 cm;
  float distance;
  glm::vec3 center;
  glm::vec3 up;

  bool leftButtonPressed = false;

  glm::vec2 lastMousePosition;
  glm::vec2 mousePositionOnLeftButton;

  void onMouseDown(int key, int mods);
  void onMouseUp(int key, int mods);
  void onMouseMove(glm::vec2 point);
  void onScroll(double w, double v);
  void createCommand();

 public:
  CameraControlCommandProvider(CommandAcceptor *, render::Camera *);
};
}
}