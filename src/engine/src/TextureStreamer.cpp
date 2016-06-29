#include "TextureStreamer.hpp"
namespace oa {
namespace render {
void TextureStreamer::setup() {
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, type,
               GL_UNSIGNED_BYTE, 0);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  newTexture = true;

  // glGenBuffers(2, pbos);

  // auto num_bytes = width * height * bytes;
  // for (int i = 0; i < 2; ++i) {
  // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbos[i]);
  // glBufferData(GL_PIXEL_UNPACK_BUFFER, num_bytes, NULL, GL_STREAM_DRAW);
  //}
}

TextureStreamer::TextureStreamer(int w, int h, int type)
    : width(w), height(h), type(type) {
  bytes = 0;
  if (type == GL_RGBA)
    bytes = 4;
  else
    bytes = 3;
  setup();
}

void TextureStreamer::setSize(int w, int h) {
  width = w;
  height = h;
  glDeleteTextures(1, &texture);
  glDeleteBuffers(2, pbos);
  setup();
}
void TextureStreamer::update(const unsigned char *buffer) {
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, type,
               GL_UNSIGNED_BYTE, buffer);
  // glTexImage2D(GL_TEXTURE_2D,
  // readIx = (readIx + 1) % 2;
  // writeIx = (readIx + 1) % 2;
  // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbos[readIx]);
  // glBindTexture(GL_TEXTURE_2D, texture);
  // glTexSubImage2d(GL_TEXTURE_2D, 0, 0, 0, width, height, type,
  // GL_UNSIGNED_BYTE, 0);

  // glBindBuffer(GL_
}
TextureStreamer::~TextureStreamer() { glDeleteTextures(1, &texture); }
bool TextureStreamer::isChanged() { return newTexture; }
render::Uniform *TextureStreamer::getUniform() {
  auto u = new render::TextureUniform(texture);
  newTexture = false;
  return u;
}
}
}
