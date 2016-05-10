#pragma once
#include <memory>
#include "SolarSystem.hpp"
#include "engine/TextureCreator.hpp"
#include "engine/MeshFabric.hpp"
#include "engine/TextureCreatorFabric.hpp"


namespace oa {
namespace game {
class SolarSystemCreator {
  std::vector<render::TextureCreator *> textureCreators;
  std::unique_ptr<SolarSystem> solarSystem;
  void parsePlanet(boost::property_tree::ptree::value_type &);
  render::MeshFabric meshFabric;
  render::TextureCreatorFabric textureCreatorFabric;
  void createSkyBox(boost::property_tree::ptree &);
  render::Mesh *sunMesh;
  void createTextureCreator(boost::property_tree::ptree &);


 public:
  SolarSystemCreator();
  void createSolarSystem(std::string filepath);
  void setupUniformUpdaters(const CelestialCameraManager *);
  std::unique_ptr<SolarSystem> getSolarSystem();
  std::vector<render::TextureCreator *> getTextureCreators();
};
}
}
