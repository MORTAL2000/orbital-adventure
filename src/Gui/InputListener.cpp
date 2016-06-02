#include <iostream>
#include "InputListener.hpp"
namespace oa {
namespace gui {
void InputListener::onMouseUp(int key, int mods) {
  //if (!context) {
    //std::cout << "context is nullptr\n";
    //return;
  //}
  // context->ProcessMouseMove(point.x, point.y, 0);
  //context->ProcessMouseButtonUp(key, mods);
}
void InputListener::onMouseDown(int key, int mods) {
  //if (!context) {
    //std::cout << "context is nullptr\n";
    //return;
  //}
  // context->ProcessMouseMove(point.x, point.y, 0);
  //context->ProcessMouseButtonDown(key, mods);
}

void InputListener::onMouseMove(glm::vec2 point) {
  //if (!context) {
    //std::cout << "context is nullptr\n";
    //return;
  //}
  //context->ProcessMouseMove(point.x, point.y, 0);
}

//void InputListener::setContext(Rocket::Core::Context *ctx) { context = ctx; }
}
}
