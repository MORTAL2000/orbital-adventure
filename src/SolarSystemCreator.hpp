#pragma once
#include <memory>
#include "Filter.hpp"
#include "SolarSystem.hpp"
#include "engine/MeshFabric.hpp"
#include "engine/TextureCreator.hpp"
#include "engine/TextureCreatorFabric.hpp"

namespace oa {
namespace game {
class SolarSystemCreator {
  const CelestialCameraManager *cameraManager;
  std::vector<render::TextureCreator *> textureCreators;
  std::unique_ptr<SolarSystem> solarSystem;
  std::vector<render::Filter *> renderFilters;
  void parsePlanet(boost::property_tree::ptree::value_type &);
  render::MeshFabric meshFabric;
  render::TextureCreatorFabric textureCreatorFabric;
  void createSkyBox(boost::property_tree::ptree &);
  render::Mesh *sunMesh;
  void createTextureCreator(boost::property_tree::ptree &);
  void createFilters(boost::property_tree::ptree &, std::string);

 public:
  SolarSystemCreator();
  void createSolarSystem(std::string filepath);
  void withCamerManager(const CelestialCameraManager *);
  std::vector<render::Filter *> &&getRenderFilters();
  std::unique_ptr<SolarSystem> getSolarSystem();
  std::vector<render::TextureCreator *> getTextureCreators();
};
}
}
