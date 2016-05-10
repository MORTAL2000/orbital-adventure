#include <boost/filesystem.hpp>
#include "TextureManager.hpp"
#include <iostream>
#include "UniformFabric.hpp"
namespace oa {
namespace render {
using namespace boost::property_tree;
void UniformFabric::setRootDir(std::string r) { rootDir = r; }
Uniform* UniformFabric::create(ptree& uniform) {
  std::string type = uniform.get("type", "");
  if (type == "sampler2D") {
    std::string value = uniform.get("value", "");
    boost::filesystem::path p(rootDir);
    p = p.parent_path() / value;
    auto textureId = TextureManager::instance()->loadTexture(p.string());
    return new TextureUniform(textureId);
  }
  std::cerr << "WARNING! Could not create uniform returning null ptr\n";
  return nullptr;
}
}
}
