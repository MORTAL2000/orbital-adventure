#include "Camera.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace oa {
namespace render {

void Camera::lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
  this->setMatrix(glm::lookAt(eye, center, up));
}

glm::dmat4 Camera::getProjectionMatrix() { return projectionMatrix; }
glm::dmat4 Camera::getProjectionMatrix() const { return projectionMatrix; }
glm::dmat4 Camera::getCameraMatrix() { return getMatrix(); }
}
}
