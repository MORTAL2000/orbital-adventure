#pragma once
#include "GLFWWrapper.hpp"
#include "TextureManager.hpp"
#include "Uniform.hpp"

namespace oa {
namespace render {
class TextureStreamer {
  GLuint texture;
  GLuint pbos[2];
  int width, height, bytes, type;
  int readIx = 0, writeIx = 0;
  bool newTexture = true;
  void setup();

 public:
  TextureStreamer(int, int, int);  // width, height,  type;
  void update(const unsigned char *);
  void setType(int);
  void setSize(int, int);
  bool isChanged();

  render::Uniform *getUniform();
  ~TextureStreamer();
};
}
}
