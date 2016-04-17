#include "PerspectiveCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace oa {
namespace render {
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
