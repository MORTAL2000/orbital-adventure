#include <iostream>
#include "Geometry.hpp"
#include "GeometryLODInstaller.hpp"
#include "GeometryManager.hpp"
#include "LODInstaller.hpp"
#include "Mesh.hpp"
#include "MeshFabric.hpp"
#include "PersonalClippingMatrixInstaller.hpp"
#include "PersonalClippingMesh.hpp"
#include "ShaderManager.hpp"
#include "SkyboxUniformInstaller.hpp"
#include "TextureManager.hpp"

namespace oa {
namespace render {
using namespace boost::property_tree;

Mesh *MeshFabric::createSkyboxMesh(std::vector<std::string> &textures,
                                   std::string vertexShaderPath,
                                   std::string fragmentShaderPath) {
  boost::filesystem::path root(rootDir);
  auto program = ShaderProgramManager::instance()->loadProgram(
      (root.parent_path() / vertexShaderPath).string(),
      (root.parent_path() / fragmentShaderPath).string());
  float boxSize = 1e9;
  auto geometry = GeometryManager::instance()->createSkyboxGeometry(boxSize);
  Mesh *mesh = new Mesh(program, geometry);
  for (auto &path : textures) {
    path = (root.parent_path() / path).string();
  }
  auto u = new CubemapUniform(
      TextureManager::instance()->loadCubemapTexture(textures));
  auto installer = new SkyboxUniformInstaller(boxSize);
  mesh->setUniformValue("CubeMap", u);
  mesh->addUniformInstaller(installer);
  return mesh;
}

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
  auto uInstallers = meshDescription.get_child("uniform-installers");
  for (ptree::value_type &p : uInstallers) {
    ptree ui = p.second;
    mesh->addUniformInstaller(createUniformInstaller(ui, mesh));
  }
  return mesh;
}
void MeshFabric::setRootDir(std::string r) { rootDir = r; }

UniformInstaller *MeshFabric::createUniformInstaller(ptree &uniform,
                                                     Mesh *mesh) {
  std::string type = uniform.get("type", "");
  std::cout << "Create installer " << type << "\n";
  if (type == "GeometryLODInstaller") {
    int width = uniform.get("totalWidth", 1);
    int height = uniform.get("totalHeight", 1);
    return new GeometryLODInstaller(mesh, glm::ivec2(width, height));
  }
  if (type == "PersonalClippingMatrixInstaller") {
    return new PersonalClippingMatrixInstaller(mesh);
  }
  if (type == "LODInstaller") {
    std::string root = uniform.get("root", "");
    boost::filesystem::path path(rootDir);
    path = path.parent_path() / root;

    std::string ext = uniform.get("filetype", "");
    int width = uniform.get("totalWidth", 0);
    int height = uniform.get("totalHeight", 0);
    return new LODInstaller(
        mesh, LODTextureManager(path.string(), width, height, ext));
  }
}

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
