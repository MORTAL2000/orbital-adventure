#include "InputListener.hpp"
#include <iostream>
#include "GLFWWrapper.hpp"
namespace oa {
namespace gui {
InputListener::InputListener(View *v) : view(v) {}
void InputListener::onMouseUp(int b, int) { view->injectMouseUp(b); }
void InputListener::onMouseDown(int b, int m) { view->injectMouseDown(b); }
void InputListener::onMouseMove(glm::vec2 p) {
  view->injectMouseMove(p.x, p.y);
}
void InputListener::onScroll(double x, double y) {
  view->injectMouseWheel(x, y);
}
void InputListener::onKeyUp(int k, int s, int m) {
  std::cout << "up \n";
  view->injectKeyboardUp(k, s, m);
}
void InputListener::onKeyDown(int k, int s, int m) {
  view->injectKeyboardDown(k, s, m);
  std::cout << "down " << k << "\n";
}
void InputListener::onChar(unsigned int ch) { std::cout << "oc" << ch << "\n"; }
void InputListener::resize(int w, int h) {}
}
}
