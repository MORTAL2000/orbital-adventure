#include <iostream>
#include "Geometry.hpp"
#include "GeometryManager.hpp"
#include "Mesh.hpp"
#include "MeshFabric.hpp"
#include "PersonalClippingMesh.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"

namespace oa {
namespace render {
using namespace boost::property_tree;

Mesh *MeshFabric::meshOfType(std::string type, ShaderProgram *sp,
                             geometry::Geometry *geometry) {
  if (type == "Mesh") return new Mesh(sp, geometry);
  if (type == "PersonalClippingMesh")
    return new PersonalClippingMesh(sp, geometry);
}
Mesh *MeshFabric::createMesh(ptree &meshDescription) {
  using namespace boost::filesystem;
  std::string meshType = meshDescription.get<std::string>("type");

  std::cout << meshType << "\n";

  boost::filesystem::path root(rootDir);
  std::string vertexShaderPath = meshDescription.get("vertexShader", "no");
  std::string fragmentShaderPath = meshDescription.get("fragmentShader", "no");
  ShaderProgram *sp = ShaderProgramManager::instance()->loadProgram(
      (root.parent_path() / vertexShaderPath).string(),
      (root.parent_path() / fragmentShaderPath).string());

  ptree geometryProps = meshDescription.get_child("geometry");
  geometry::Geometry *geometry =
      GeometryManager::instance()->loadGeometry(geometryProps);
  Mesh *mesh = meshOfType(meshType, sp, geometry);

  auto uniforms = meshDescription.get_child("uniforms");
  for (ptree::value_type &p : uniforms) {
    ptree uniform = p.second;
    mesh->setUniformValue(p.first, createUniform(uniform));
  }
  return mesh;
}
void MeshFabric::setRootDir(std::string r) { rootDir = r; }
Uniform *MeshFabric::createUniform(ptree &uniform) {
  std::string type = uniform.get("type", "");
  if (type == "sampler2D") {
    std::string value = uniform.get("value", "");
    boost::filesystem::path p(rootDir);
    p = p.parent_path() / value;
    auto textureId = TextureManager::instance()->loadTexture(p.string());
    return new TextureUniform(textureId);
  }
  std::cerr << "returning null ptr";
  return nullptr;
}
}
}
