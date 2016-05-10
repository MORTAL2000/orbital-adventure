#include <boost/filesystem.hpp>
#include <iostream>
#include "GeometryManager.hpp"
#include "ShaderManager.hpp"
#include "TextureCreatorFabric.hpp"
namespace oa {
namespace render {
using namespace boost::property_tree;
void TextureCreatorFabric::setRootDir(std::string r) { rootDir = r; }
void TextureCreatorFabric::setUniformInstallerFabric(
    UniformInstallerFabric *ptr) {
  uniformInstallerFabric.reset(ptr);
}
void TextureCreatorFabric::setUniformFabric(UniformFabric *ptr) {
  uniformFabric.reset(ptr);
}
void TextureCreatorFabric::setDefaultVertexShaderPath(std::string shp) {
  boost::filesystem::path p(rootDir);
  p = p.parent_path() / shp;
  vShader = p.string();
}
TextureCreator *TextureCreatorFabric::make(ptree &tCreator) {
  using namespace boost::filesystem;

  boost::filesystem::path root(rootDir);
  std::string shader = tCreator.get("shader", "no");

  ShaderProgram *sp = ShaderProgramManager::instance()->loadProgram(
      (root.parent_path() / vShader).string(),
      (root.parent_path() / shader).string());

  std::string target = tCreator.get<std::string>("target");
  bool needsDepthTest = tCreator.get("needsDepthTest", false);
  int width = tCreator.get("width", 0);
  int height = tCreator.get("height", 0);
  geometry::Geometry *geometry =
      GeometryManager::instance()->createPatchGeometry();
  TextureCreator *tc =
      new TextureCreator(sp, target, needsDepthTest, width, height);

  auto uniforms = tCreator.get_child_optional("uniforms");
  if (uniforms) {
    for (ptree::value_type &p : *uniforms) {
      ptree uniform = p.second;
      tc->setUniformValue(p.first, uniformFabric->create(uniform));
    }
  }
  auto uInstallers = tCreator.get_child("uniform-installers");
  if (!uniformInstallerFabric) {
    std::cerr << "Uniform Instaleer fabric is not set\n";
    exit(0);
    return nullptr;
  }

  for (ptree::value_type &p : uInstallers) {
    ptree ui = p.second;
    tc->addUniformInstaller(uniformInstallerFabric->createUniformInstaller(ui));
  }
  return tc;
}
}
}
