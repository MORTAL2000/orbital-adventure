#include <boost/filesystem.hpp>
#include <iostream>
#include "TextureManager.hpp"
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

  if (type == "vec2") {
    float x = uniform.get("value.x", 0.0f);
    float y = uniform.get("value.y", 0.0f);
    return new Vec2OwnerUniform(glm::vec2(x, y));
  }
  if (type == "vec3") {
    float x = uniform.get("value.x", 0.0f);
    float y = uniform.get("value.y", 0.0f);
    float z = uniform.get("value.z", 0.0f);
    std::cout << "U3: " << x << " . " << y << " . " << z << "\n";
    return new Vec3OwnerUniform(glm::vec3(x, y, z));
  }
  if (type == "int") {
    int value = uniform.get("value", 0);
    return new IntOwnerUniform(value);
  }
  if (type == "float") {
    float value = uniform.get("value", 0.0f);
    return new FloatOwnerUniform(value);
  }

  std::cerr << "WARNING! Could not create uniform returning null ptr\n";
  return nullptr;
}
}
}
