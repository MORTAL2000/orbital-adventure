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
  viewMap["science"] = "../data/gui/science-tree-view.rml";
  viewMap["design"] = "../data/gui/rocket-design-view.rml";
  science =
      std::unique_ptr<EventListener>(new EventListener(this, "show-science"));
  design =
      std::unique_ptr<EventListener>(new EventListener(this, "show-design"));
}

Gui::EventListener::EventListener(Gui *g, std::string s)
    : eventName(s), gui(g) {}
void Gui::EventListener::ProcessEvent(Rocket::Core::Event &evt) {
  // std::cout << "Got event " << eventName << "\n";
  if (eventName == "show-science") gui->showView("science");
  if (eventName == "show-design") gui->showView("design");
}

void Gui::showView(std::string name) {
  std::string path = viewMap[name];
  if (currentView) {
    std::cout << "remove current main\n";
    context->UnloadDocument(currentView);
  }
  currentView = context->LoadDocument(path.c_str());

  Rocket::Core::Element *scienceButton =
                            currentView->GetElementById("science-button"),
                        *designButton =
                            currentView->GetElementById("design-button");

  scienceButton->AddEventListener("click", science.get(), true);
  designButton->AddEventListener("click", design.get(), true);

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
  Rocket::Controls::Initialise();
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
