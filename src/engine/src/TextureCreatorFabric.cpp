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
void TextureCreatorFabric::setDefaultGeometryShaderPath(std::string shp) {
  boost::filesystem::path p(rootDir);
  p = p.parent_path() / shp;
  gShader = p.string();
}
void TextureCreatorFabric::setDefaultVertexShaderPath(std::string shp) {
  boost::filesystem::path p(rootDir);
  p = p.parent_path() / shp;
  vShader = p.string();
}

TextureCreator *TextureCreatorFabric::make(ptree &tCreator) {
  using namespace boost::filesystem;

  std::vector<std::string> targets;
  boost::filesystem::path root(rootDir);
  std::string shader = tCreator.get("shader", "no");
  auto target = tCreator.get_optional<std::string>("target");
  if (target)
    targets.push_back(*target);
  else {
    auto ts = tCreator.get_child_optional("targets");
    if (ts) {
      for (auto &t : *ts) targets.push_back(t.second.get_value<std::string>());
    }
  }
  if (targets.size() == 0) std::cerr << "WARNING! Targets are not defined\n";
  bool needsDepthTest = tCreator.get("needsDepthTest", true);
  int width = tCreator.get("width", 0);
  int height = tCreator.get("height", 0);
  int depth = tCreator.get("depth", 1);

  ShaderProgram *sp;
  if (depth == 1) {
    sp = ShaderProgramManager::instance()->loadProgram(
        (root.parent_path() / vShader).string(),
        (root.parent_path() / shader).string());
  } else {
    std::cout << "create GEOMETRY SHADER\n";
    sp = ShaderProgramManager::instance()->loadProgram(
        (root.parent_path() / vShader).string(),
        (root.parent_path() / shader).string(),
        (root.parent_path() / gShader).string());
  }

  geometry::Geometry *geometry =
      GeometryManager::instance()->createPatchGeometry();
  TextureCreator *tc =
      new TextureCreator(sp, targets, needsDepthTest, width, height, depth);

  auto uniforms = tCreator.get_child_optional("uniforms");
  if (uniforms) {
    for (ptree::value_type &p : *uniforms) {
      ptree uniform = p.second;
      tc->setUniformValue(p.first, uniformFabric->create(uniform));
    }
  }
  auto uInstallers = tCreator.get_child_optional("uniform-installers");
  if (!uniformInstallerFabric) {
    std::cerr << "Uniform Instaleer fabric is not set\n";
    exit(0);
    return nullptr;
  }

  if (uInstallers) {
    for (ptree::value_type &p : *uInstallers) {
      ptree ui = p.second;
      tc->addUniformInstaller(
          uniformInstallerFabric->createUniformInstaller(ui));
    }
  }
  return tc;
}
}
}
