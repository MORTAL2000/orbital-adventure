#include "RocketForm.hpp"
#include <nanogui/label.h>
#include <nanogui/layout.h>
#include "widgets/Panel.hpp"
namespace oa {
namespace gui {
RocketForm::RocketForm(nanogui::Widget *p) : parent(p) {
  using namespace nanogui;
  me = new Panel(parent);
  this->hide();
  me->setLayout(
      new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 6));
  new Label(me, "rocket");
}
void RocketForm::hide() { me->setVisible(false); }
void RocketForm::show() { me->setVisible(true); }
}
}
