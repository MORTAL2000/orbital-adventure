#include "StageForm.hpp"
#include <nanogui/button.h>
#include <nanogui/entypo.h>
#include <nanogui/label.h>
#include <nanogui/layout.h>
#include <nanogui/textbox.h>
#include <iostream>
#include "widgets/Panel.hpp"
#include "widgets/Popup.hpp"
namespace oa {
namespace gui {
StageForm::StageForm(nanogui::Widget *p) : parent(p) {
  using namespace nanogui;
  me = new Widget(parent);
  this->hide();
  me->setLayout(new BoxLayout(Orientation::Vertical, Alignment::Middle, 0, 0));
  auto saveLoader = new Widget(me);
  saveLoader->setLayout(new GroupLayout);
  new Label(saveLoader, "Stage");
  auto stageLabel = new TextBox(saveLoader);
  stageLabel->setValue("50 ");
  {
    auto sz = stageLabel->size();
    stageLabel->setFixedSize(Vector2i(150, sz.y()));
  }
  stageLabel->setEditable(true);
  stageLabel->setAlignment(TextBox::Alignment::Left);
  stageLabel->setCallback([](auto str) {
    std::cout << "got " << str << "\n";
    return true;
  });
  auto saveButton = new Button(saveLoader, "", ENTYPO_ICON_SAVE);
  saveButton->setCallback([]() { std::cout << "lets save stage\n"; });

  auto loadButton = new PopupButton(saveLoader, "", ENTYPO_ICON_SAVE);
  popups.push_back(loadButton);
  auto lbPopup = loadButton->popup();
  auto searchStage = new TextBox(lbPopup);
  searchStage->setEditable(true);
  lbPopup->setLayout(
      new BoxLayout(Orientation::Vertical, Alignment::Minimum, 0, 0));
  searchStage->setCallback([](auto search) {
    std::cout << "search for ... " << search << "\n";
    return true;
  });
  new Label(lbPopup, "Here would be list of stages");
}
void StageForm::hide() {
  me->setVisible(false);
  for (auto p : popups) {
    p->popup()->setVisible(false);
  }
}
void StageForm::show() { me->setVisible(true); }
}
}
