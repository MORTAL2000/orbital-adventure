#pragma once
#undef NDEBUG
#include <nanogui/nanogui.h>
#include <map>
#include "../engine/Renderer.hpp"
#include "InputListener.hpp"

namespace oa {
namespace gui {
class Gui {
  std::map<std::string, std::string> viewMap;
  const std::string guiRendererTarget;
  std::unique_ptr<nanogui::Screen> nanoguiScreen;
  std::unique_ptr<InputListener> inputListener;
  int width, height;
  nanogui::Widget *mainButtonsPanel;
  nanogui::Widget *builderWindow;
  nanogui::Widget *scienceWindow;
  void initBuilderWindow();
  void initScienceWindow();

 public:
  ~Gui();
  Gui();
  void init();
  void setRenderer(render::Renderer *renderer);
  input::InputListener *getInputListener();
  void showView(std::string name);
  void render(float timeDiff);
  void setDimentions(int, int);
};
}
}
