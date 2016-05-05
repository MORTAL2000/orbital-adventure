#pragma once
#include <glm/mat4x4.hpp>
#include "Object.hpp"

namespace oa {
namespace render {
class Camera : public Object {
 protected:
  glm::mat4 projectionMatrix;
  glm::vec3 direction;
  glm::vec3 up;

 public:
  virtual glm::vec3 getDirection();
  virtual glm::vec3 getDirection() const;
  virtual glm::vec3 getUp();
  virtual glm::vec3 getUp() const;
  virtual const glm::mat4 &getCameraMatrix();
  virtual const glm::mat4 &getProjectionMatrix();
  virtual const glm::mat4 &getProjectionMatrix() const;
  virtual Camera *changeClipping(double, double) const = 0;
  virtual Camera *clone() const = 0;

  virtual void lookAt(glm::vec3, glm::vec3, glm::vec3);
  virtual ~Camera(){};
};
}
}
