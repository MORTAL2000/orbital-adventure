#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include "Camera.hpp"
#include "LanguageUtils.hpp"

namespace oa {
namespace render {
using namespace utils;

glm::vec3 Camera::getDirection() { return direction; }
glm::vec3 Camera::getDirection() const { return direction; }
glm::vec3 Camera::getUp() { return up; }
glm::vec3 Camera::getUp() const { return up; }
void Camera::lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
  position = eye;
  direction = eye - center;
  this->up = up;
  this->setMatrix(glm::lookAt(eye, center, up));
}

const glm::mat4 &Camera::getProjectionMatrix() { return projectionMatrix; }
const glm::mat4 &Camera::getProjectionMatrix() const {
  return projectionMatrix;
}
const glm::mat4 &Camera::getCameraMatrix() { return getMatrix(); }
}
}
