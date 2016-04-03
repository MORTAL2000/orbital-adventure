#pragma once
#include <string>
#include <map>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "CelestialObject.hpp"
#include "PlanetID.hpp"
#include "Mesh.hpp"
#include "MeshFabric.hpp"

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

 private:
  render::MeshFabric meshFabric;
  std::map<PlanetID, CelestialPtr> celestialsMap;
  std::map<PlanetID, MeshPtr> celestialMeshes;

  std::string planetFilePath;
  void parsePlanet(boost::property_tree::ptree::value_type &);
  // MeshPtr createMesh(boost::property_tree::ptree meshDescription);
};
}
}
