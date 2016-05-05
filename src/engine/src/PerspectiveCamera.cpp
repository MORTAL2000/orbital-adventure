#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "PerspectiveCamera.hpp"

namespace oa {
namespace render {
Camera* PerspectiveCamera::clone() const {
  auto newCamera = new PerspectiveCamera(fov, aspect, near, far);
  newCamera->lookAt(this->getPosition(),
                    this->getPosition() - this->getDirection(), this->getUp());
  return newCamera;
}
PerspectiveCamera::PerspectiveCamera(double fov, double aspect, double near,
                                     double far)
    : fov(fov), aspect(aspect), near(near), far(far) {
  projectionMatrix = glm::perspective(fov, aspect, near, far);
}

Camera* PerspectiveCamera::changeClipping(double n, double f) const {
  auto newCamera = new PerspectiveCamera(fov, aspect, n, f);
  newCamera->setMatrix(this->getMatrix());
  return newCamera;
}
}
}
