#pragma once
#include <boost/property_tree/ptree.hpp>
#include "Mesh.hpp"
#include "UniformInstaller.hpp"
namespace oa {
namespace render {

class UniformInstallerFabric {
 public:
  virtual UniformInstaller *createUniformInstaller(
      boost::property_tree::ptree &uniform) = 0;
  virtual UniformInstaller *createUniformInstaller(
      boost::property_tree::ptree &uniform, Mesh *mesh) = 0;
};
}
}
