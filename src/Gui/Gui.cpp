#include <Rocket/Core/FontDatabase.h>
#include <iostream>
#include "Gui.hpp"

namespace oa {
namespace gui {
float Gui::SystemIface::GetElapsedTime() {
  time += 0.5;
  return time;
};

Gui::Gui() : context(nullptr), renderer(nullptr) {}
void Gui::setRenderer(render::Renderer *r) {
  // renderer = r;
  rendererIface.setRenderer(renderer);
}
Rocket::Core::Context *Gui::getContext() { return context; }
void Gui::load() {
  Rocket::Core::SetSystemInterface(&systemIface);
  Rocket::Core::SetRenderInterface(&rendererIface);
  Rocket::Core::Initialise();
  context =
      Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(400, 400));
  if (!context) {
    std::cout << "ERROR: context is not created\n";
  }

  // Rocket::Controls::Initialise();
  // context->LoadDocument("ui/testwindow.rml");
}
}
}
