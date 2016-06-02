#pragma once
#include "../engine/InputListener.hpp"

namespace oa {
namespace gui {
class InputListener : public input::InputListener {

  void onMouseMove(glm::vec2 point);
  void onMouseDown(int, int);
  void onMouseUp(int, int);

 public:
  //void setContext(Rocket::Core::Context *);
};
}
}
