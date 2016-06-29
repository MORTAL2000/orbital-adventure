#pragma once
#include <Awesomium/WebView.h>
#include "TextureStreamer.hpp"
namespace oa {
namespace gui {
class View {
  Awesomium::WebView *view;
  render::TextureStreamer *streamer;
  unsigned char *textureData;

 public:
  View(std::string url, int width, int height);
  void resize(int, int);
  void update();
  bool textureRecreated();
  render::Uniform *getUniform();
  ~View();
};
}
}
