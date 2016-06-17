// clang format off
 #include <iostream>
#include "Gui.hpp"
#include <iostream>
// clang format on

namespace oa {
namespace gui {
void Gui::init(){
  int error = glGetError();
  std::cout <<std:: hex<< error << "got error ibefore \n" ; 

  nvCtx = nvgCreateGL3(NVG_DEBUG|NVG_ANTIALIAS|NVG_STENCIL_STROKES);
  nvgGlobalAlpha(nvCtx, 0.6);

}
Gui::Gui()
    :  
      renderer(nullptr),
      guiRendererTarget("gui") {
}

void Gui::showView(std::string name) {
  std::string path = viewMap[name];
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
}

void Gui::render(float td) {
  glClear(GL_STENCIL_BUFFER_BIT);
  nvgBeginFrame(nvCtx, width, height, 1);
  __renderSomething();
  nvgEndFrame(nvCtx);
}

void Gui::setDimentions(int w, int h) {
  width = w;
  height = h;
  renderer->setupTarget(guiRendererTarget, 1);
  renderer->addStencilBufferFor(guiRendererTarget);
}

void Gui::load() {
}
}
}
