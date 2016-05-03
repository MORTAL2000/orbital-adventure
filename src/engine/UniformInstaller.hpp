#pragma once
#include "UniformHolder.hpp"
#include "Camera.hpp"

namespace oa {
namespace render {
class UniformInstaller {
 public:
  virtual ~UniformInstaller(){};
  virtual void install(UniformHolder *, const Camera *, double t) = 0;
};
}
}
