#pragma once
#include "Camera.hpp"
namespace oa {
namespace render {
class PerspectiveCamera : public Camera {
  double fov, aspect, near, far;

 public:
  PerspectiveCamera(double fov, double aspect, double near, double far);
  Camera *changeClipping(double, double) const;
};
}
}
