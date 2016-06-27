#pragma once
#include <nanogui/screen.h>
#include "View.hpp"
namespace oa {
namespace gui {
class PayloadForm : public View {
  nanogui::Widget *parent;
  nanogui::Widget *me;

 public:
  PayloadForm(nanogui::Widget *);
  void show() override;
  void hide() override;
};
}
}

