#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include "Camera.hpp"

namespace oa {
namespace render {

void Camera::lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
  this->setMatrix(glm::lookAt(eye, center, up));
}

const glm::mat4 &Camera::getProjectionMatrix() { return projectionMatrix; }
const glm::mat4 &Camera::getProjectionMatrix() const {
  return projectionMatrix;
}
const glm::mat4 &Camera::getCameraMatrix() { return getMatrix(); }
}
}
