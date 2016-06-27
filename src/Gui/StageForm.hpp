#pragma once
#include <nanogui/screen.h>
#include "View.hpp"
#include "widgets/Popup.hpp"
namespace oa {
namespace gui {
class StageForm : public View {
  nanogui::Widget *parent;
  nanogui::Widget *me;
  std::vector<PopupButton *> popups;

 public:
  StageForm(nanogui::Widget *);
  void show() override;
  void hide() override;
};
}
}
