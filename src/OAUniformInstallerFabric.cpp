#include <boost/filesystem.hpp>
#include <iostream>
#include "CurrentPlanetAtmosphere.hpp"
#include "GeometryLODInstaller.hpp"
#include "LODInstaller.hpp"
#include "OAUniformInstallerFabric.hpp"
#include "PersonalClippingMatrixInstaller.hpp"
#include "TimeInstaller.hpp"

namespace oa {
namespace game {
using namespace boost::property_tree;
using namespace render;

OAUniformInstallerFabric::OAUniformInstallerFabric(
    const SolarSystem *s, const CelestialCameraManager *mgr)
    : solarSystem(s), cameraManager(mgr) {}
void OAUniformInstallerFabric::setRootDir(std::string s) { rootDir = s; }

UniformInstaller *OAUniformInstallerFabric::createUniformInstaller(
    ptree &uInstaller) {
  std::string type = uInstaller.get("type", "");
  if (type == "CurrentPlanetAtmosphere")
    return new CurrentPlanetAtmosphere(solarSystem, cameraManager);
  std::cerr << "WARNING! Uniform installer not found: " << type << "\n";
  return nullptr;
}

UniformInstaller *OAUniformInstallerFabric::createUniformInstaller(
    ptree &uInstaller, Mesh *mesh) {
  std::string type = uInstaller.get("type", "");
  if (type == "GeometryLODInstaller") {
    int width = uInstaller.get("totalWidth", 1);
    int height = uInstaller.get("totalHeight", 1);
    return new GeometryLODInstaller(mesh, glm::ivec2(width, height));
  }
  if (type == "TimeInstaller") {
    return new TimeInstaller;
  }
  if (type == "PersonalClippingMatrixInstaller") {
    return new PersonalClippingMatrixInstaller(mesh);
  }
  if (type == "LODInstaller") {
    std::string root = uInstaller.get("root", "");
    boost::filesystem::path path(rootDir);
    path = path.parent_path() / root;

    std::string ext = uInstaller.get("filetype", "");
    int width = uInstaller.get("totalWidth", 0);
    int height = uInstaller.get("totalHeight", 0);
    return new LODInstaller(
        mesh, LODTextureManager(path.string(), width, height, ext));
  }
  std::cerr << "WARNING! Uniform installer not found: " << type << "\n";
  return nullptr;
}
}
}
