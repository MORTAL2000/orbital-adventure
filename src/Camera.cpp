#include "Camera.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace oa {
namespace render {

/*
void Camera::lookAt(glm::vec3 center, glm::quat rotation, float distance) {
// need to calculate eye
// auto m = glm::mat4_cast(rotation);
up = rotation * up;
dir = rotation * dir;
glm::vec3 eye = (dir * distance) + center;
std::cout << "WARNING! Camera::lookAt is not implemented\n"
          << "center" << dir.x << ", " << dir.y << ", " << dir.z
          << "  D: " << distance << "\n";

// lookAt(eye, center, up);
this->setMatrix(glm::lookAt(eye, center, up));
}
*/

// void Camera::updateLookAt() { lookAt(center, rotation, distance); }

void Camera::lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
  dir = glm::normalize(eye - center);
  this->center = center;
  this->up = up;
  this->distance = glm::length(center - eye);
  this->setMatrix(glm::lookAt(eye, center, up));
}

glm::dmat4 Camera::getProjectionMatrix() { return projectionMatrix; }
glm::dmat4 Camera::getCameraMatrix() { return getMatrix(); }
}
}
