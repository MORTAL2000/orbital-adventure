#pragma once
#include <glm/vec2.hpp>
namespace oa {
namespace input {
class InputListener {
 public:
  virtual void onMouseDown(int, int){};
  virtual void onMouseUp(int, int){};
  virtual void onMouseMove(glm::vec2){};

  virtual void onKeyDown(int, int, int){};
  virtual void onKeyUp(int, int, int){};
  virtual void onScroll(double, double){};
  virtual void onChar(unsigned int){};
  virtual void resize(int, int){};
  virtual ~InputListener(){};
};
}
}
