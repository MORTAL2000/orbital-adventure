#include <nanogui/screen.h>
#include "../engine/InputListener.hpp"

namespace oa {
namespace gui {
class InputListener : public input::InputListener {
  nanogui::Screen *screen;
  void onMouseMove(glm::vec2) override;
  void onMouseUp(int, int) override;
  void onMouseDown(int, int) override;
  void onKeyUp(int, int, int) override;
  void onKeyDown(int, int, int) override;
  void onScroll(double, double) override;
  void onChar(unsigned int) override;
  void resize(int, int) override;

 public:
  InputListener(nanogui::Screen *);
};
}
}
