#pragma once
#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "Mesh.hpp"
#include "Uniform.hpp"
#include "UniformFabric.hpp"
#include "UniformInstallerFabric.hpp"

namespace oa {
namespace render {
class MeshFabric {
  std::unique_ptr<UniformInstallerFabric> uniformInstallerFabric;
  std::unique_ptr<UniformFabric> uniformFabric;
  std::string rootDir;
  virtual Mesh *meshOfType(std::string, ShaderProgram *, geometry::Geometry *);

 public:
  void setUniformFabric(UniformFabric *);
  void setUniformInstallerFabric(UniformInstallerFabric *);
  Mesh *createMesh(boost::property_tree::ptree &);
  Mesh *createSkyboxMesh(std::vector<std::string> &textures, std::string,
                         std::string);
  void setRootDir(std::string);
};
}
}
