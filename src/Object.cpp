#include "Object.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>

namespace oa {
namespace render {
Object::Object()
    : position(0.f, 0.f, 0.f),
      rotation(1.0f, 0.f, 0.f, 0.f),
      scale(1.f, 1.f, 1.f) {}

glm::mat4 Object::getMatrix() { return matrix; }
glm::mat4 Object::getMatrix() const { return matrix; }
void Object::setMatrix(glm::mat4 m) {
  matrix = m;
  glm::vec3 scew;
  glm::vec4 perspective;
  glm::decompose(matrix, scale, rotation, position, scew, perspective);
}

void Object::setPosition(glm::vec3 p) {
  position = p;
  updateMatrix();
}

void Object::setScale(glm::vec3 s) {
  scale = s;
  updateMatrix();
}

glm::quat Object::getRotation() { return rotation; }

void Object::setRotation(glm::quat r) {
  rotation = r;
  updateMatrix();
}

void Object::updateMatrix() {
  std::cout << "update matrix\n";
  auto s = glm::scale(glm::mat4(1.0f), scale);
  auto rotMat = glm::mat4_cast(rotation);
  auto p = glm::translate(glm::mat4(1.0), position);
  matrix = p * rotMat * s;
}
}
}
