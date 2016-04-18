#pragma once
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <memory>
#include <string>
#include "CelestialObject.hpp"
#include "PlanetID.hpp"
#include "engine/Mesh.hpp"
#include "engine/MeshFabric.hpp"
#include "engine/Scene.hpp"

namespace oa {
namespace game {
typedef std::unique_ptr<CelestialObject> CelestialPtr;
class SolarSystem {
 public:
  typedef std::map<PlanetID, CelestialPtr> CelestialMap;
  typedef const std::map<PlanetID, CelestialPtr> &CelestialMapRef;

 private:
  CelestialMap celestialsMap;
  render::Scene scene;

 public:
  SolarSystem();
  void addPlanet(CelestialPtr);
  void updatePlanets(long);
  const render::Scene *getScene();
  CelestialMapRef getPlanetMap() const;
};
}
}
