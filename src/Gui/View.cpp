#include "View.hpp"
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/WebCore.h>
#include <Awesomium/WebURL.h>

namespace oa {
namespace gui {
using namespace render;
using namespace Awesomium;

bool View::textureRecreated() { return streamer->isChanged(); }
Uniform* View::getUniform() { return streamer->getUniform(); }
View::View(std::string url, int w, int h) {
  view = Awesomium::WebCore::instance()->CreateWebView(w, h);
  view->LoadURL(WebURL(ToWebString(url)));
  textureData = new unsigned char[w * h * 4];
  streamer = TextureManager::instance()->createStreamer(w, h, GL_RGBA);
}

void View::update() {
  BitmapSurface* texture = static_cast<BitmapSurface*>(view->surface());
  auto buffer = texture->buffer();
  streamer->update(buffer);
}

void View::resize(int w, int h) {
  delete textureData;

  textureData = new unsigned char[w * h * 4];
  streamer->setSize(w, h);
  view->Resize(w, h);
}

View::~View() { view->Destroy(); }
}
}
