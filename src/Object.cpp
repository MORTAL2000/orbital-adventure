#include "Object.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace oa {
namespace render {

glm::dmat4 Object::getMatrix() { return matrix; }

void Object::setPosition(glm::dvec3 p) {
  position = p;
  glm::translate(matrix, position);
}

void Object::setScale(glm::dvec3 s) {
  scale = s;
  glm::scale(matrix, scale);
}

void Object::setRotation(glm::dquat r) {
  matrix *= mat4_cast(r);
  rotation = r;
}
}
}
