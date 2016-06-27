#pragma once
#include <nanogui/screen.h>
#include "View.hpp"
namespace oa {
namespace gui {
class RocketForm : public View {
  nanogui::Widget *parent;
  nanogui::Widget *me;

 public:
  RocketForm(nanogui::Widget *);
  void show() override;
  void hide() override;
};
}
}

