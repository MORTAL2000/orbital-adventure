#pragma once
#include <Awesomium/WebView.h>
#include "TextureStreamer.hpp"

#define map_key(a, b) \
  case GLFW_KEY_##a:  \
    return Awesomium::KeyCodes::AK_##b;

namespace oa {
namespace gui {
int glfw2Awesomium(int);
class View {
  Awesomium::WebView *view;
  render::TextureStreamer *streamer;
  unsigned char *textureData;

 public:
  void injectMouseMove(int, int);
  void injectMouseDown(int);
  void injectMouseUp(int);
  void injectMouseWheel(int, int);
  void injectKeyboardUp(int, int, int);
  void injectKeyboardDown(int, int, int);

  View(std::string url, int width, int height);
  void resize(int, int);
  void update();
  bool textureRecreated();
  render::Uniform *getUniform();
  ~View();
};
}
}
