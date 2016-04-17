#pragma once
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <memory>
#include <string>
#include "CelestialObject.hpp"
#include "engine/Mesh.hpp"
#include "engine/MeshFabric.hpp"
#include "PlanetID.hpp"
#include "engine/Scene.hpp"

namespace oa {
namespace game {
typedef std::unique_ptr<CelestialObject> CelestialPtr;
typedef render::Mesh *MeshPtr;
class SolarSystem {
 public:
  typedef std::map<PlanetID, CelestialPtr> CelestialMap;
  typedef const std::map<PlanetID, CelestialPtr> &CelestialMapRef;
  SolarSystem();
  void createPlanets();
  void updatePlanets(long);
  const std::map<PlanetID, MeshPtr> *const getCelestialMeshes() const;
  const render::Scene *getScene();
  CelestialMapRef getPlanetMap() const;

 private:
  render::MeshFabric meshFabric;
  CelestialMap celestialsMap;
  std::map<PlanetID, MeshPtr> celestialMeshes;

  std::string planetFilePath;
  void parsePlanet(boost::property_tree::ptree::value_type &);
  render::Scene scene;
};
}
}
