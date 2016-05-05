#pragma once
#include <map>
#include "GLFWWrapper.hpp"

namespace oa {
namespace render {
class TextureManager {
  TextureManager();
  std::map<std::string, GLuint> loadedTextures;
  GLuint loadPngTexture(std::string);
  GLuint loadPngTexture(
      std::string, std::function<void(GLuint&, int, int, int, const char*)>);
  GLuint loadJpegTexture(std::string);
  GLuint loadJpegTexture(
      std::string, std::function<void(GLuint&, int, int, int, const char*)>);
  bool isPng(std::string);
  bool isJpeg(std::string);

  void texture(GLuint&, int, int, int, const char*);
  void cubemap(int, int, int, int, const char*);

 public:
  static TextureManager* instance();

  GLuint loadTexture(std::string filepath);
  GLuint loadCubemapTexture(std::vector<std::string>& files);
};
}
}
