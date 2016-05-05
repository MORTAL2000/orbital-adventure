#pragma once
#include <memory>
#include "SolarSystem.hpp"
#include "engine/MeshFabric.hpp"

namespace oa {
namespace game {
class SolarSystemCreator {
  std::unique_ptr<SolarSystem> solarSystem;
  void parsePlanet(boost::property_tree::ptree::value_type &);
  render::MeshFabric meshFabric;
  void createSkyBox(boost::property_tree::ptree &);

 public:
  SolarSystemCreator();
  void createSolarSystem(std::string filepath);
  void setupUniformUpdaters(const CelestialCameraManager *);
  std::unique_ptr<SolarSystem> getSolarSystem();
};
}
}
