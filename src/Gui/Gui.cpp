#include "Gui.hpp"
#include <boost/filesystem.hpp>
#include <iostream>
#include "GLFWWrapper.hpp"

namespace oa {
namespace gui {

Gui::~Gui() {}
Gui::GuiUniformInstaller::GuiUniformInstaller(Gui *g) : gui(g) {}
Gui::Gui(std::string dataRoot) {
  Awesomium::WebConfig config;
  config.log_level = Awesomium::kLogLevel_Verbose;
  this->webcore = Awesomium::WebCore::Initialize(config);

  boost::filesystem::path p(dataRoot);
  p /= "gui/guiRenderer.glsl";
  filter = new render::Filter(p.string());
  filter->addUniformInstaller(new Gui::GuiUniformInstaller(this));
  view = new View("data:text/html, <html>Hello world</html>", width, height);
}

void Gui::GuiUniformInstaller::install(render::UniformHolder *to,
                                       const render::Camera *, double) {
  auto v = gui->view;
  if (v->textureRecreated()) {
    to->setUniformValue("guiTexture", v->getUniform());
  }
}

void Gui::showView(std::string) {}

void Gui::setRenderer(render::Renderer *r) { r->pushFilter(filter); }

void Gui::render(float) {
  webcore->Update();
  view->update();
}

void Gui::setDimentions(int w, int h) {
  width = w;
  height = h;
  view->resize(w, h);
}
input::InputListener *Gui::getInputListener() { return inputListener.get(); }

void Gui::init() {}
}
}
