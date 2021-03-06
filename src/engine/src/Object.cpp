#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include "Object.hpp"

namespace oa {
namespace render {
Object::Object()
    : position(0.f, 0.f, 0.f),
      rotation(1.0f, 0.f, 0.f, 0.f),
      scale(1.f, 1.f, 1.f) {}

const glm::mat4& Object::getMatrix() { return matrix; }
const glm::mat4& Object::getMatrix() const { return matrix; }
void Object::setMatrix(glm::mat4 m) {
  matrix = m;
  // glm::vec3 scew;
  // glm::vec4 perspective;
  // glm::decompose(matrix, scale, rotation, position, scew, perspective);
}

void Object::setPosition(glm::vec3 p) {
  position = p;
  updateMatrix();
}

void Object::setScale(glm::vec3 s) {
  scale = s;
  updateMatrix();
}
glm::vec3 Object::getPosition() const { return position; }
glm::vec3 Object::getScale() const { return scale; }

const glm::quat& Object::getRotation() { return rotation; }

void Object::setRotation(glm::quat r) {
  rotation = r;
  updateMatrix();
}

void Object::updateMatrix() {
  auto s = glm::scale(glm::mat4(1.0f), scale);
  auto rotMat = glm::mat4_cast(rotation);
  auto p = glm::translate(glm::mat4(1.0f), position);

  matrix = p * rotMat * s;

  /*
  std::cout << "MAT\n\n";
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cout << matrix[i][j] << "  ";
    }
    std::cout << "\n";
  }
  */
}
}
}
