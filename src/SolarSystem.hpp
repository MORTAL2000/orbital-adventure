#pragma once
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <memory>
#include <string>
#include "CelestialObject.hpp"
#include "Mesh.hpp"
#include "MeshFabric.hpp"
#include "PlanetID.hpp"
#include "Scene.hpp"

namespace oa {
namespace game {
typedef std::unique_ptr<CelestialObject> CelestialPtr;
typedef render::Mesh *MeshPtr;
class SolarSystem {
 public:
  SolarSystem();
  void createPlanets();
  void updatePlanets(long);
  const std::map<PlanetID, MeshPtr> *const getCelestialMeshes() const;
  const render::Scene *getScene();

 private:
  render::MeshFabric meshFabric;
  std::map<PlanetID, CelestialPtr> celestialsMap;
  std::map<PlanetID, MeshPtr> celestialMeshes;

  std::string planetFilePath;
  void parsePlanet(boost::property_tree::ptree::value_type &);
  render::Scene scene;
};
}
}
