#pragma once
#include <nanogui/widget.h>
#include <nanovg.h>
namespace oa {
namespace gui {
using namespace nanogui;

class NANOGUI_EXPORT ImageButton : public Widget {
 public:
  enum class SizePolicy { Fixed, Expand };

  ImageButton(Widget *parent, int image = 0,
              SizePolicy policy = SizePolicy::Fixed);

  void setImage(int img) { mImage = img; }
  int image() const { return mImage; }

  void setPolicy(SizePolicy policy) { mPolicy = policy; }
  SizePolicy policy() const { return mPolicy; }

  virtual Vector2i preferredSize(NVGcontext *ctx) const override;
  virtual void draw(NVGcontext *ctx) override;
  void setCallback(const std::function<void()> &callback) {
    mCallback = callback;
  }

  bool mouseButtonEvent(const Vector2i &p, int button, bool down,
                        int modifiers) override;

 protected:
  std::function<void()> mCallback;
  int mImage;
  SizePolicy mPolicy;
};
}
}
