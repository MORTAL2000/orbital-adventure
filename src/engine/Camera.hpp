#pragma once
#include <glm/mat4x4.hpp>
#include "Object.hpp"

namespace oa {
namespace render {
class Camera : public Object {
 protected:
  glm::mat4 projectionMatrix;

 public:
  virtual const glm::mat4 &getCameraMatrix();
  virtual const glm::mat4 &getProjectionMatrix();
  virtual const glm::mat4 &getProjectionMatrix() const;
  virtual Camera *changeClipping(double, double) const = 0;
  virtual void lookAt(glm::vec3, glm::vec3, glm::vec3);
  virtual ~Camera(){};
};
}
}
