#include <boost/filesystem.hpp>
#include "Planet.hpp"
#include "SolarSystem.hpp"
#include "Star.hpp"

namespace oa {
namespace game {
SolarSystem::SolarSystem() {}

const render::Scene *SolarSystem::getScene() { return &scene; }

inline float random() { return float(std::rand()) / (std::pow(2, 32) / 2); }

const std::map<PlanetID, CelestialPtr> &SolarSystem::getPlanetMap() const {
  return this->celestialsMap;
}

void SolarSystem::addPlanet(CelestialPtr planet) {
  PlanetID id(planet->getName());

  scene.addMesh(planet->getMesh());
  celestialsMap.insert(std::make_pair(id, std::move(planet)));
}
}
}
