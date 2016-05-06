#pragma once
#include "engine/Mesh.hpp"
#include "engine/UniformInstaller.hpp"
namespace oa {
namespace game {
class SunDirectionUniformInstaller : public render::UniformInstaller {
  void install(render::UniformHolder *, const render::Camera *, double);
  render::Mesh *sun, *me;

 public:
  SunDirectionUniformInstaller(render::Mesh *sun, render::Mesh *me);
};
}
}
