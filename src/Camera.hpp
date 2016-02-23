#pragma once
#include <glm/mat4x4.hpp>
namespace oa {
namespace render {
class Camera : public Object {
 protected:
  glm::dmat4 projectionMatrix;

 public:
  virtual glm::dmat4 getCameraMatrix();
  virtual glm::dmat4 getProjectionMatrix();
  virtual Camera *changeClipping(double, double) const;
  virtual ~Camera(){};
};
}
}
