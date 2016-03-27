#pragma once
#include <glm/mat4x4.hpp>
#include "Object.hpp"

namespace oa {
namespace render {
class Camera : public Object {
 protected:
  glm::dmat4 projectionMatrix;
  float distance;
  glm::vec3 center;
  glm::vec3 up;
  glm::vec3 dir;

 public:
  virtual glm::dmat4 getCameraMatrix();
  virtual glm::dmat4 getProjectionMatrix();
  // virtual void updateLookAt();
  virtual Camera *changeClipping(double, double) const = 0;
  virtual void lookAt(glm::vec3, glm::vec3, glm::vec3);
  // virtual void lookAt(glm::vec3, glm::quat, float);
  virtual ~Camera(){};
};
}
}
