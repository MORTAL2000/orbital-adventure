#pragma once
#include <Rocket/Controls.h>
#include <Rocket/Core.h>
#include <map>
#include "../engine/Renderer.hpp"
#include "GuiRender.hpp"
namespace oa {
namespace gui {
class Gui {
  struct EventListener : public Rocket::Core::EventListener {
    std::string eventName;
    void ProcessEvent(Rocket::Core::Event&);
    EventListener(std::string);
  };

  std::unique_ptr<EventListener> science, design;

  Rocket::Core::Context* context;
  render::Renderer* renderer;
  Rocket::Core::ElementDocument* currentView;
  int width, height;
  struct SystemIface : public Rocket::Core::SystemInterface {
    float time = 0;
    float GetElapsedTime() override;
  };

  SystemIface systemIface;
  GuiRenderer rendererIface;
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
  Rocket::Core::Context* getContext();
};
}
}
