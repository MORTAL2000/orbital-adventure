#pragma once
#include "Camera.hpp"
#include "UniformHolder.hpp"

namespace oa {
namespace render {
class UniformInstaller {
 public:
  virtual ~UniformInstaller(){};
  virtual void install(UniformHolder *, const Camera *, double t) = 0;
};
}
}
