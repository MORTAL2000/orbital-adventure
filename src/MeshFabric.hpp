#pragma once
#include "Mesh.hpp"
#include "Uniform.hpp"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace oa {
namespace render {
class MeshFabric {
  std::string rootDir;

 public:
  Uniform *createUniform(boost::property_tree::ptree &);
  Mesh *createMesh(boost::property_tree::ptree &);
  void setRootDir(std::string);
};
}
}
