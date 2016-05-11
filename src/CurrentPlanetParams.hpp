#pragma once
#include "CelestialObject.hpp"
#include "engine/UniformInstaller.hpp"

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
