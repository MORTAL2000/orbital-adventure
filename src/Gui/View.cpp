#include "View.hpp"
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/WebCore.h>
#include <Awesomium/WebURL.h>
#include <iostream>

namespace oa {
namespace gui {
using namespace render;
using namespace Awesomium;

void View::injectMouseUp(int k) {
  // clang-format off
  switch(k){
    case 0: {view->InjectMouseUp(kMouseButton_Left); break;}
    case 2: {view->InjectMouseUp(kMouseButton_Middle); break;}
    case 1: {view->InjectMouseUp(kMouseButton_Right); break;}
  }
  // clang-format on
};
void View::injectMouseDown(int k) {
  // clang-format off
  switch(k){
    case 0: {view->InjectMouseDown(kMouseButton_Left); break;}
    case 2: {view->InjectMouseDown(kMouseButton_Middle); break;}
    case 1: {view->InjectMouseDown(kMouseButton_Right); break;}
  }
  // clang-format on
}
void View::injectMouseMove(int x, int y) { view->InjectMouseMove(x, y); }
void View::injectMouseWheel(int x, int y) { view->InjectMouseWheel(y, x); }

void View::injectKeyboardUp(int k, int scancode, int mod) {
  Awesomium::WebKeyboardEvent event;
  event.type = Awesomium::WebKeyboardEvent::kTypeKeyUp;
  event.virtual_key_code = glfw2Awesomium(k);
  char* buf = new char[20];
  Awesomium::GetKeyIdentifierFromVirtualKeyCode(event.virtual_key_code, &buf);
  strcpy(event.key_identifier, buf);
  event.modifiers = mod;
  view->InjectKeyboardEvent(event);
  delete[] buf;
}

void View::injectKeyboardDown(int k, int scancode, int mod) {
  Awesomium::WebKeyboardEvent event;
  event.type = Awesomium::WebKeyboardEvent::kTypeKeyDown;
  event.virtual_key_code = glfw2Awesomium(k);
  char* buf = new char[20];
  Awesomium::GetKeyIdentifierFromVirtualKeyCode(event.virtual_key_code, &buf);
  strcpy(event.key_identifier, buf);
  event.modifiers = mod;
  view->InjectKeyboardEvent(event);
  delete[] buf;
}

bool View::textureRecreated() { return streamer->isChanged(); }
Uniform* View::getUniform() { return streamer->getUniform(); }
View::View(std::string url, int w, int h) {
  view = Awesomium::WebCore::instance()->CreateWebView(w, h);
  view->LoadURL(WebURL(ToWebString(url)));
  textureData = new unsigned char[w * h * 4];
  streamer = TextureManager::instance()->createStreamer(w, h, GL_RGBA);
  view->Focus();
}

void View::update() {
  BitmapSurface* texture = static_cast<BitmapSurface*>(view->surface());
  if (!texture) {
    std::cout << "no surface returned\n";
    return;
  }
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

int glfw2Awesomium(int key) {
  switch (key) {
    // clang-format off
    map_key(A, A)
    map_key(B, B)
    map_key(C, C)
    map_key(D, D)
    map_key(E, E)
    map_key(F, F)
    map_key(G, G)
    map_key(H, H)
    map_key(I, I)
    map_key(J, J)
    map_key(K, K)
    map_key(L, L)
    map_key(M, M)
    map_key(N, N)
    map_key(O, O)
    map_key(P, P)
    map_key(Q, Q)
    map_key(R, R)
    map_key(S, S)
    map_key(T, T)
    map_key(U, U)
    map_key(V, V)
    map_key(W, W)
    map_key(X, X)
    map_key(Y, Y)
    map_key(Z, Z)
    // clang-format on
  }
}
}
}
