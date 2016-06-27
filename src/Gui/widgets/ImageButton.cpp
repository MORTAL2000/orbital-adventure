#include "ImageButton.hpp"
namespace oa {
namespace gui {
using namespace nanogui;

ImageButton::ImageButton(Widget *parent, int image, SizePolicy policy)
    : Widget(parent), mImage(image), mPolicy(policy), mCallback([]() {}) {}

Vector2i ImageButton::preferredSize(NVGcontext *ctx) const {
  if (!mImage) return Vector2i(0, 0);
  int w, h;
  nvgImageSize(ctx, mImage, &w, &h);
  return Vector2i(w, h);
}

void ImageButton::draw(NVGcontext *ctx) {
  if (!mImage) return;
  Vector2i p = mPos;
  Vector2i s = Widget::size();

  int w, h;
  nvgImageSize(ctx, mImage, &w, &h);

  if (mPolicy == SizePolicy::Fixed) {
    if (s.x() < w) {
      h = (int)std::round(h * (float)s.x() / w);
      w = s.x();
    }

    if (s.y() < h) {
      w = (int)std::round(w * (float)s.y() / h);
      h = s.y();
    }
  } else {  // mPolicy == Expand
    // expand to width
    h = (int)std::round(h * (float)s.x() / w);
    w = s.x();

    // shrink to height, if necessary
    if (s.y() < h) {
      w = (int)std::round(w * (float)s.y() / h);
      h = s.y();
    }
  }

  NVGpaint imgPaint = nvgImagePattern(ctx, p.x(), p.y(), w, h, 0, mImage, 1.0);

  nvgBeginPath(ctx);
  nvgRect(ctx, p.x(), p.y(), w, h);
  nvgFillPaint(ctx, imgPaint);
  nvgFill(ctx);
}

bool ImageButton::mouseButtonEvent(const Vector2i &p, int button, bool down,
                                   int modifiers) {
  if (!down) mCallback();
  return true;
}
}
}
