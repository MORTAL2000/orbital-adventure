#pragma once
#include "CelestialCameraManager.hpp"
#include "SolarSystem.hpp"
#include "engine/UniformInstallerFabric.hpp"

namespace oa {
namespace game {
class OAUniformInstallerFabric : public render::UniformInstallerFabric {
  const SolarSystem *solarSystem;
  const CelestialCameraManager *cameraManager;
  std::string rootDir;
  render::UniformInstaller *createUniformInstaller(
      boost::property_tree::ptree &uInstaller);
  render::UniformInstaller *createUniformInstaller(
      boost::property_tree::ptree &uInstaller, render::Mesh *mesh);

 public:
  OAUniformInstallerFabric(const SolarSystem *, const CelestialCameraManager *);
  void setRootDir(std::string r);
};
}
}
