#pragma once
#include <glm/mat4x4.hpp>
#include "Object.hpp"

namespace oa {
namespace render {
class Camera : public Object {
 protected:
  glm::dmat4 projectionMatrix;

 public:
  virtual glm::dmat4 getCameraMatrix();
  virtual glm::dmat4 getProjectionMatrix();
  virtual glm::dmat4 getProjectionMatrix() const;
  virtual Camera *changeClipping(double, double) const = 0;
  virtual void lookAt(glm::vec3, glm::vec3, glm::vec3);
  virtual ~Camera(){};
};
}
}
