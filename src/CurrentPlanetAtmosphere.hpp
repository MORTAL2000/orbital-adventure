#pragma once
#include "CelestialCameraManager.hpp"
#include "SolarSystem.hpp"
#include "engine/UniformInstaller.hpp"

namespace oa {
namespace game {
class CurrentPlanetAtmosphere : public render::UniformInstaller {
  std::vector<std::string> precalculatedTextures;
  const SolarSystem* solarSystem;
  const CelestialCameraManager* cameraManager;
  void install(render::UniformHolder*, const render::Camera*, double t);

 public:
  CurrentPlanetAtmosphere(const SolarSystem* ptr,
                          const CelestialCameraManager*);
};
}
}
