#pragma once
#include "UniformInstaller.hpp"
namespace oa {
namespace render {
class SkyboxUniformInstaller : public UniformInstaller {
  float skyboxSize;
  void install(UniformHolder *, const Camera *, double t);

 public:
  SkyboxUniformInstaller(float s);
};
}
}
