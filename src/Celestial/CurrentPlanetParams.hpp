#pragma once
#include "../engine/UniformInstaller.hpp"
#include "CelestialObject.hpp"

namespace oa {
namespace game {
class CurrentPlanetParams : public render::UniformInstaller {
  const CelestialObject* object;
  void install(render::UniformHolder*, const render::Camera*, double t);

 public:
  CurrentPlanetParams(const CelestialObject* ptr);
};
}
}
