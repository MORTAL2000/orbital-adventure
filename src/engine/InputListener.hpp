#pragma once
#include <glm/vec2.hpp>
namespace oa {
namespace input {
class InputListener {
 public:
  virtual void onMouseDown(int key, int mods){};
  virtual void onMouseUp(int key, int mods){};
  virtual void onMouseMove(glm::vec2 point){};

  virtual void onKeyDown(int keyCode, int scancode, int mods){};
  virtual void onKeyUp(int keyCode, int scancode, int mods){};
  virtual void onScroll(double w, double v){};
  virtual void onChar(unsigned int){};
  virtual void resize(int, int){};
  virtual ~InputListener(){};
};
}
}
