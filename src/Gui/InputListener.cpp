#include "InputListener.hpp"
#include <iostream>
#include "GLFWWrapper.hpp"
namespace oa {
namespace gui {
InputListener::InputListener(View *v) : view(v) {}
void InputListener::onMouseUp(int b, int m) {}
void InputListener::onMouseDown(int b, int m) {}
void InputListener::onMouseMove(glm::vec2 p) {}
void InputListener::onScroll(double x, double y) {}
void InputListener::onKeyUp(int k, int s, int m) { std::cout << "ku\n"; }
void InputListener::onKeyDown(int k, int s, int m) { std::cout << "kd\n"; }
void InputListener::onChar(unsigned int ch) { std::cout << "oc\n"; }
void InputListener::resize(int w, int h) {}
}
}
