#pragma once
#include "GLFWWrapper.hpp"
#include <map>

namespace oa {
namespace render {
class TextureManager {
  TextureManager();
  std::map<std::string, GLuint> loadedTextures;
  GLuint loadPngTexture(std::string);
  GLuint loadJpegTexture(std::string);
  bool isPng(std::string);
  bool isJpeg(std::string);

 public:
  static TextureManager* instance();

  GLuint loadTexture(std::string filepath);
};
}
}
