#pragma once
#include <Rocket/Core.h>
#include "../engine/InputListener.hpp"

namespace oa {
namespace gui {
class InputListener : public input::InputListener {
  Rocket::Core::Context *context;
  void onMouseMove(glm::vec2 point);

 public:
  void setContext(Rocket::Core::Context *);
};
}
}
