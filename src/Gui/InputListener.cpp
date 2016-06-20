#include "InputListener.hpp"
#include "GLFWWrapper.hpp"
namespace oa {
namespace gui {
InputListener::InputListener(nanogui::Screen *s) : screen(s) {}
void InputListener::onMouseUp(int b, int m) {
   screen->mouseButtonCallbackEvent(b, GLFW_RELEASE, m);
}
void InputListener::onMouseDown(int b, int m) {
   screen->mouseButtonCallbackEvent(b, GLFW_PRESS, m);
}
void InputListener::onMouseMove(glm::vec2 p) {
   screen->cursorPosCallbackEvent(p.x, p.y);
}
void InputListener::onScroll(double x, double y) {
   screen->scrollCallbackEvent(x, y);
}
void InputListener::onKeyUp(int k, int s, int m) {
   screen->keyboardEvent(k, s, GLFW_RELEASE, m);
}
void InputListener::onKeyDown(int k, int s, int m) {
   screen->keyboardEvent(k, s, GLFW_PRESS, m);
}
void InputListener::onChar(unsigned int ch) {
   screen->charCallbackEvent(ch);
}
void InputListener::resize(int w, int h) {
   screen->resizeCallbackEvent(w, h);
}
}
}
