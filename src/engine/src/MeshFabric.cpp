#include <iostream>
#include "Geometry.hpp"
#include "GeometryManager.hpp"
#include "Mesh.hpp"
#include "MeshFabric.hpp"
#include "ShaderManager.hpp"
#include "SkyboxUniformInstaller.hpp"
#include "TextureManager.hpp"

namespace oa {
namespace render {
using namespace boost::property_tree;

void MeshFabric::setUniformFabric(UniformFabric *uf) {
  uniformFabric = std::unique_ptr<UniformFabric>(uf);
}

void MeshFabric::setUniformInstallerFabric(UniformInstallerFabric *uif) {
  uniformInstallerFabric = std::unique_ptr<UniformInstallerFabric>(uif);
}

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
  // if (type == "PersonalClippingMesh")
  // return new PersonalClippingMesh(sp, geometry);
  return nullptr;
}

Mesh *MeshFabric::createMesh(ptree &meshDescription) {
  using namespace boost::filesystem;
  std::string meshType = meshDescription.get<std::string>("type");

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
    mesh->setUniformValue(p.first, uniformFabric->create(uniform));
  }
  auto uInstallers = meshDescription.get_child("uniform-installers");
  if (!uniformInstallerFabric) {
    std::cerr << "Uniform Instaleer fabric is not set\n";
    exit(0);
    return nullptr;
  }

  for (ptree::value_type &p : uInstallers) {
    ptree ui = p.second;
    mesh->addUniformInstaller(
        uniformInstallerFabric->createUniformInstaller(ui, mesh));
  }
  return mesh;
}
void MeshFabric::setRootDir(std::string r) { rootDir = r; }
}
}
