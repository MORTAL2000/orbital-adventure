#include <Rocket/Core/FontDatabase.h>
#include <iostream>
#include "Gui.hpp"

namespace oa {
namespace gui {
float Gui::SystemIface::GetElapsedTime() {
  // time += 0.5;
  return time;
};

Gui::~Gui() {
  context->RemoveReference();
  Rocket::Core::Shutdown();
}
Gui::Gui()
    : context(nullptr),
      renderer(nullptr),
      currentView(nullptr),
      guiRendererTarget("gui") {
  viewMap["main"] = "../data/gui/main.rml";
}

void Gui::showView(std::string name) {
  std::string path = viewMap[name];
  currentView = context->LoadDocument(path.c_str());
  currentView->Show();
  currentView->RemoveReference();
}
void Gui::setRenderer(render::Renderer *r) {
  renderer = r;
  renderer->setupTarget(guiRendererTarget, 4);
  rendererIface.setRenderer(renderer);
}
Rocket::Core::Context *Gui::getContext() { return context; }

void Gui::render(float td) {
  systemIface.time += td;
  renderer->bindTarget(guiRendererTarget);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  context->Render();
  glDisable(GL_BLEND);
  renderer->unbindTargets();
}

void Gui::setDimentions(int w, int h) {
  width = w;
  height = h;
  if (context) context->SetDimensions(Rocket::Core::Vector2i(w, h));
  rendererIface.setDimentions(w, h);
  renderer->setupTarget(guiRendererTarget, 1);
}

void Gui::load() {
  Rocket::Core::SetSystemInterface(&systemIface);
  Rocket::Core::SetRenderInterface(&rendererIface);
  Rocket::Core::Initialise();
  Rocket::Core::FontDatabase::LoadFontFace(
      "../data/gui/fonts/Leto-One-Defect.otf");
  Rocket::Core::FontDatabase::LoadFontFace(
      "../data/gui/fonts/Delicious-Bold.otf");
  Rocket::Core::FontDatabase::LoadFontFace(
      "../data/gui/fonts/ArialRegular.woff");
  context =
      Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(400, 400));
  if (!context) {
    std::cout << "ERROR: context is not created\n";
  }
}
}
}
