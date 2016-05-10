#pragma once
#include "engine/UniformInstallerFabric.hpp"

namespace oa {
namespace game {
class OAUniformInstallerFabric : public render::UniformInstallerFabric {
  std::string rootDir;
  render::UniformInstaller *createUniformInstaller(
      boost::property_tree::ptree &uInstaller);
  render::UniformInstaller *createUniformInstaller(
      boost::property_tree::ptree &uInstaller, render::Mesh *mesh);

 public:
  void setRootDir(std::string r);
};
}
}
