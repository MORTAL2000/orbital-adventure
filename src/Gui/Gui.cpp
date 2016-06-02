//#include <Rocket/Core/FontDatabase.h>
// clang format off
 #include <iostream>
#include "Gui.hpp"
#include <nanovg_gl.h>
#include "nanovg_gl_utils.h"
#include <iostream>
// clang format on

namespace oa {
namespace gui {
// float Gui::SystemIface::GetElapsedTime() {
// time += 0.5;
// return time;
//};

// Gui::~Gui() {
// context->RemoveReference();
// Rocket::Core::Shutdown();
//}
void Gui::init(){
  int error = glGetError();
  std::cout <<std:: hex<< error << "got error ibefore \n" ; 

  nvCtx = nvgCreateGL3(NVG_DEBUG|NVG_ANTIALIAS|NVG_STENCIL_STROKES);
  nvgGlobalAlpha(nvCtx, 0.6);
  //fb = nvgluCreateFramebuffer(nvCtx, width, height,NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
  //if(fb == NULL) std::cout << "failed to create fb\n";

}
Gui::Gui()
    :  //: context(nullptr),
      renderer(nullptr),
      // currentView(nullptr),
      guiRendererTarget("gui") {
  // viewMap["main"] = "../data/gui/main.rml";
  // viewMap["science"] = "../data/gui/science-tree-view.rml";
  // viewMap["design"] = "../data/gui/rocket-design-view.rml";
  // science =
  // std::unique_ptr<EventListener>(new EventListener(this, "show-science"));
  // design =
  // std::unique_ptr<EventListener>(new EventListener(this, "show-design"));
}

// Gui::EventListener::EventListener(Gui *g, std::string s)
//: eventName(s), gui(g) {}
// void Gui::EventListener::ProcessEvent(Rocket::Core::Event &evt) {
//// std::cout << "Got event " << eventName << "\n";
// if (eventName == "show-science") gui->showView("science");
// if (eventName == "show-design") gui->showView("design");
//}

void Gui::showView(std::string name) {
  std::string path = viewMap[name];
  // if (currentView) {
  // std::cout << "remove current main\n";
  // context->UnloadDocument(currentView);
  //}
  // currentView = context->LoadDocument(path.c_str());
  //
  // Rocket::Core::Element *scienceButton =
  // currentView->GetElementById("science-button"),
  //*designButton =
  // currentView->GetElementById("design-button");
  //
  // scienceButton->AddEventListener("click", science.get(), true);
  // designButton->AddEventListener("click", design.get(), true);
  //
  // currentView->Show();
  // currentView->RemoveReference();
}
void Gui::__renderSomething(){
  nvgBeginPath(nvCtx);
  nvgRect(nvCtx, 0, 0, 10, 10); 
  nvgStrokeColor(nvCtx, nvgRGBA(255, 0,0, 255));
  nvgStroke(nvCtx);

  nvgBeginPath(nvCtx);
  nvgRect(nvCtx, 0, 0, 100, 100); 
  nvgFillColor(nvCtx, nvgRGBA(10, 255,0, 80));
  nvgFill(nvCtx);

}

void Gui::setRenderer(render::Renderer *r) {
  renderer = r;
  //renderer->setupTarget(guiRendererTarget, 1);
  //renderer->addStencilBufferFor(guiRendererTarget);
}
// Rocket::Core::Context *Gui::getContext() { return context; }

void Gui::render(float td) {
  // systemIface.time += td;
  //nvgluBindFramebuffer(fb);
  //renderer->bindTarget(guiRendererTarget);
  //glViewport(0,0, width, height);
  glClear(GL_STENCIL_BUFFER_BIT);
  nvgBeginFrame(nvCtx, width, height, 1);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  __renderSomething();
  //int error = glGetError();
  //std::cout <<std:: hex<< error << "got error ibefore \n" ; 
  // context->Render();
  //glDisable(GL_BLEND);
  nvgEndFrame(nvCtx);
  //renderer->unbindTargets();
}

void Gui::setDimentions(int w, int h) {
  width = w;
  height = h;
  //nvgluDeleteFramebuffer(fb);

  //fb = nvgluCreateFramebuffer(nvCtx, width, height,NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);

  renderer->setupTarget(guiRendererTarget, 1);
  renderer->addStencilBufferFor(guiRendererTarget);
}

void Gui::load() {
}
}
}
