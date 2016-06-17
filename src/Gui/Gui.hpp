#pragma once
#include "nanovg.h"
#include <map>
#include "../engine/Renderer.hpp"
namespace oa {
namespace gui {
class Gui {
  struct NVGcontext *nvCtx;
  render::Renderer* renderer;
  int width, height;
  std::map<std::string, std::string> viewMap;
  const std::string guiRendererTarget;

  void __renderSomething();
 public:
  void init();
  Gui();
  void load();
  void setRenderer(render::Renderer* renderer);
  void showView(std::string name);
  void render(float timeDiff);
  void setDimentions(int, int);
};
}
}
