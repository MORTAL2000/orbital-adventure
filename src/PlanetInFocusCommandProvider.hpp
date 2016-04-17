#pragma once
#include "CommandProvider.hpp"
#include "engine/InputListener.hpp"
#include "SolarSystem.hpp"
#include "CelestialCameraManager.hpp"

namespace oa {
namespace game {
class PlanetInFocusCommandProvider : public CommandProvider,
                                     public input::InputListener {
  SolarSystem* solarSystem;
  CelestialCameraManager* cameraMgr;

 public:
  PlanetInFocusCommandProvider(CommandAcceptor*, SolarSystem* ss,
                               CelestialCameraManager* cm);
};
}
}
