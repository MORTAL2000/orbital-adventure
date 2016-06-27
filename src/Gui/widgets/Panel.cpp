#include "Panel.hpp"
#include <nanogui/theme.h>
namespace oa {
namespace gui {
nanogui::Vector2i Panel::preferredSize(NVGcontext *ctx) const {
  if (mFixedSize.x() > 0) {
    return mFixedSize;
  }

  nanogui::Vector2i sz(0, 0);
  for (auto i : mChildren) {
    sz += i->preferredSize(ctx);
  }
  return sz;
}

void Panel::draw(NVGcontext *ctx) {
  int ds = mTheme->mWindowDropShadowSize, cr = mTheme->mWindowCornerRadius;
  nvgStrokeWidth(ctx, 1.0f);
  nvgBeginPath(ctx);
  nvgRect(ctx, mPos.x() - 0.5f, mPos.y() - 0.5f, mSize.x() + 1, mSize.y() + 1);
  nvgStrokeColor(ctx, nvgRGBA(255, 0, 0, 255));
  nvgStroke(ctx);
  nvgSave(ctx);
  nvgBeginPath(ctx);
  nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);

  nvgFillColor(ctx, mMouseFocus ? mTheme->mWindowFillFocused
                                : mTheme->mWindowFillUnfocused);
  nvgFill(ctx);

  nvgTranslate(ctx, mPos.x(), mPos.y());
  for (auto ch : mChildren) ch->draw(ctx);
  nvgTranslate(ctx, -mPos.x(), -mPos.y());
}
}
}
