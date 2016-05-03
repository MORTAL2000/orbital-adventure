#pragma once
#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "Mesh.hpp"
#include "Uniform.hpp"

namespace oa {
namespace render {
class MeshFabric {
  std::string rootDir;

 public:
  Uniform *createUniform(boost::property_tree::ptree &);
  UniformInstaller *createUniformInstaller(boost::property_tree::ptree &,
                                           Mesh *);
  Mesh *createMesh(boost::property_tree::ptree &);
  Mesh *meshOfType(std::string, ShaderProgram *, geometry::Geometry *);
  void setRootDir(std::string);
};
}
}
