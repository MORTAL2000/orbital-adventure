#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace oa {
namespace render {
class Object {
 protected:
  glm::mat4 matrix;
  Object *parent;
  glm::quat rotation;
  glm::vec3 position;
  glm::vec3 scale;
  void updateMatrix();

 public:
  virtual void setPosition(glm::vec3);
  virtual void setScale(glm::vec3);
  virtual void setRotation(glm::quat);
  virtual glm::quat getRotation();
  virtual glm::mat4 getMatrix();
  virtual glm::mat4 getMatrix() const;
  virtual void setMatrix(glm::mat4);
  Object();
  virtual ~Object(){};
};
}
}
