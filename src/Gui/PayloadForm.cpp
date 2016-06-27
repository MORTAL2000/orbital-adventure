#include "PayloadForm.hpp"
#include <nanogui/label.h>
#include <nanogui/layout.h>
#include "widgets/Panel.hpp"
namespace oa {
namespace gui {
PayloadForm::PayloadForm(nanogui::Widget *p) : parent(p) {
  using namespace nanogui;
  me = new Panel(parent);
  this->hide();
  me->setLayout(
      new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 6));
  new Label(me, "Payload");
}
void PayloadForm::hide() { me->setVisible(false); }
void PayloadForm::show() { me->setVisible(true); }
}
}
