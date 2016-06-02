#pragma once
#include "nanovg.h"
#include "nanovg_gl_utils.h"
//#include <Rocket/Controls.h>
//#include <Rocket/Core.h>
#include <map>
#include "../engine/Renderer.hpp"
namespace oa {
namespace gui {
class Gui {
  struct NVGcontext *nvCtx;  //struct EventListener : public Rocket::Core::EventListener {
  NVGLUframebuffer * fb;
    //std::string eventName;
    //Gui* gui;
    //void ProcessEvent(Rocket::Core::Event&);
    //EventListener(Gui*, std::string);
  //};

  //std::unique_ptr<EventListener> science, design;

  //Rocket::Core::Context* context;
  render::Renderer* renderer;
  //Rocket::Core::ElementDocument* currentView;
  int width, height;
  //struct SystemIface : public Rocket::Core::SystemInterface {
    //float time = 0;
    //float GetElapsedTime() override;
  //};

  //SystemIface systemIface;
  //GuiRenderer rendererIface;
  std::map<std::string, std::string> viewMap;
  const std::string guiRendererTarget;

  void __renderSomething();
 public:
  void init();
  //~Gui();
  Gui();
  void load();
  void setRenderer(render::Renderer* renderer);
  void showView(std::string name);
  void render(float timeDiff);
  void setDimentions(int, int);
  //Rocket::Core::Context* getContext();
};
}
}
