#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace oa {
namespace render {
class Object {
 protected:
  glm::dmat4 matrix;
  Object *parent;
  glm::dquat rotation;
  glm::dvec3 position;
  glm::dvec3 scale;

 public:
  virtual void setPosition(glm::dvec3);
  virtual void setScale(glm::dvec3);
  virtual void setRotation(glm::dquat);
  virtual glm::dmat4 getMatrix();
  virtual ~Object(){};
};
}
}
