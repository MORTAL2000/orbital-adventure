#pragma once
#undef NDEBUG
//#include <nanogui/nanogui.h>
#include <Awesomium/WebCore.h>
#include <Awesomium/WebView.h>
#include <map>
#include "../engine/Renderer.hpp"
#include "Filter.hpp"
#include "InputListener.hpp"
#include "View.hpp"

namespace oa {
namespace gui {
class Gui {
  std::string dataRoot;
  std::unique_ptr<InputListener> inputListener;
  int width, height;
  Awesomium::WebCore *webcore;
  View *view;
  render::Filter *filter;
  struct GuiUniformInstaller : public render::UniformInstaller {
    Gui *gui;
    void install(render::UniformHolder *to, const render::Camera *, double);
    GuiUniformInstaller(Gui *);
  };

 private:
  render::Uniform *getGuiTextureUniform();
  friend void GuiUniformInstaller::install(render::UniformHolder *,
                                           const render::Camera *, double);

 public:
  ~Gui();
  Gui(std::string dataRoot);
  void init();
  void setRenderer(render::Renderer *renderer);
  input::InputListener *getInputListener();
  void showView(std::string name);
  void render(float timeDiff);
  void setDimentions(int, int);
};
}
}
