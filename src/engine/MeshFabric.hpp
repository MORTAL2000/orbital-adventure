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
  Mesh *meshOfType(std::string, ShaderProgram *, geometry::Geometry *);
  UniformInstaller *createUniformInstaller(boost::property_tree::ptree &,
                                           Mesh *);
  Uniform *createUniform(boost::property_tree::ptree &);

 public:
  Mesh *createMesh(boost::property_tree::ptree &);
  Mesh *createSkyboxMesh(std::vector<std::string> &textures, std::string,
                         std::string);
  void setRootDir(std::string);
};
}
}
