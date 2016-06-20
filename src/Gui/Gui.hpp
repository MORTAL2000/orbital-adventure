#pragma once
#include <map>
#include "../engine/Renderer.hpp"
namespace oa {
namespace gui {
class Gui {


  std::map<std::string, std::string> viewMap;
  const std::string guiRendererTarget;

 public:
  ~Gui();
  Gui();
  void load();
  void setRenderer(render::Renderer* renderer);
  void showView(std::string name);
  void render(float timeDiff);
  void setDimentions(int, int);
};
}
}
