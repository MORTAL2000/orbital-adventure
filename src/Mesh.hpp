#pragma once
#include <map>
#include <string>
#include "Object.hpp"

namespace oa {
namespace render {
class Mesh : public render::Object {
 public:
  virtual uint32_t getProgramId() = 0;
  virtual uint32_t setupGeometry() = 0;
  virtual void setupUniforms(glm::dmat4 viewProjection) = 0;
  virtual ~Mesh(){};
};
}
}
