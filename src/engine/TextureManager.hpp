#pragma once
#include <map>
#include "GLFWWrapper.hpp"

namespace oa {
namespace render {
class TextureStreamer;
class TextureManager {
  TextureManager();
  GLuint pixelBuffers[2];
  bool pixelBuffersInited = false;
  std::map<std::string, GLuint> loadedTextures;
  std::vector<std::unique_ptr<TextureStreamer>> textureStreamers;
  GLuint loadPngTexture(std::string);
  GLuint loadPngTexture(
      std::string, std::function<void(GLuint&, int, int, int, const char*)>);
  GLuint loadJpegTexture(std::string);
  GLuint loadJpegTexture(
      std::string, std::function<void(GLuint&, int, int, int, const char*)>);
  bool isPng(std::string);
  bool isJpeg(std::string);

  void texture(GLuint&, int, int, int, const char*);
  void texture(GLuint& id, int type, int width, int height, const char* data,
               int innerType);
  void cubemap(int, int, int, int, const char*);

 public:
  static TextureManager* instance();

  GLuint loadTexture(std::string filepath);
  GLuint loadCubemapTexture(std::vector<std::string>& files);
  GLuint createTexture(const unsigned char*, int, int);
  TextureStreamer* createStreamer(int, int, int);
};
}
}
