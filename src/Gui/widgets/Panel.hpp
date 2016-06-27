#pragma once
#include <nanogui/widget.h>
#include <nanovg.h>
namespace oa {
namespace gui {
class Panel : public nanogui::Widget {
  void draw(NVGcontext *ctx) override;
  nanogui::Vector2i preferredSize(NVGcontext *) const override;

 public:
  Panel(Widget *parent) : Widget(parent){};
};
}
}
