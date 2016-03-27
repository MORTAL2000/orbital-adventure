#pragma once
#include <map>
#include <string>
#include "Object.hpp"

namespace oa {
namespace render {
class Mesh : public render::Object {
 public:
  virtual uint32_t getProgramId() = 0;
  virtual void render() = 0;
  virtual void setupUniforms(glm::mat4 projection, glm::mat4 view) = 0;
  virtual ~Mesh(){};
};
}
}
