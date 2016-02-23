#pragma once
#include "Camera.hpp"
namespace oa {
namespace render {
class PerspectiveCamera : public Camera {
 public:
  PerspectiveCamera(double fov, double aspect, double near, double far);
  glm::dmat4 getProjectionMatrix();
  Camera *changeClipping(double, double);
}
}
}
