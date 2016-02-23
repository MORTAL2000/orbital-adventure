#pragma once
#include "GLFWWrapper.hpp"
#include <map>

namespace oa {
namespace render {
class TextureManager {
  TextureManager();
  std::map<std::string, GLuint> loadedTextures;

 public:
  static TextureManager *instance();

  GLuint loadTexture(std::string filepath);
};
}
}
