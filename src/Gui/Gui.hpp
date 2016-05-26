#pragma once
#include <Rocket/Controls.h>
#include <Rocket/Core.h>
#include "../engine/Renderer.hpp"
#include "GuiRender.hpp"
namespace oa {
namespace gui {
class Gui {
  Rocket::Core::Context* context;
  render::Renderer* renderer;
  struct SystemIface : public Rocket::Core::SystemInterface {
    float time = 0;
    float GetElapsedTime() override;
  };

  SystemIface systemIface;
  GuiRenderer rendererIface;

 public:
  Gui();
  void load();
  void setRenderer(render::Renderer* renderer);
  Rocket::Core::Context* getContext();
};
}
}
