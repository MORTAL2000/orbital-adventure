#include "Popup.hpp"
#include <nanogui/screen.h>
#include <nanogui/theme.h>
#include <nanovg.h>
#include <iostream>
namespace oa {
namespace gui {
using namespace nanogui;
Widget *PopupButton::getRoot() {
  Widget *p = mParent;
  while (1) {
    if (p) {
      auto np = p->parent();
      if (np)
        p = np;
      else
        return p;
    }
  }
}

PopupButton::PopupButton(Widget *parent, const std::string &caption,
                         int buttonIcon, int chevronIcon)
    : Button(parent, caption, buttonIcon), mChevronIcon(chevronIcon) {
  setFlags(Flags::ToggleButton | Flags::PopupButton);

  auto root = getRoot();

  mPopup = new Popup(root, this);
  mPopup->setSize(Vector2i(320, 250));
  mPopup->setVisible(false);
}

Vector2i PopupButton::preferredSize(NVGcontext *ctx) const {
  return Button::preferredSize(ctx) + Vector2i(15, 0);
}
// void PopupButton::setVisible(bool v) {
// Widget::setVisible(v);
// mPopup->setVisible(v);
// mPushed = false;
//}

bool PopupButton::focusEvent(bool focused) {
  auto r = Button::focusEvent(focused);
  return r;
}

bool PopupButton::mouseButtonEvent(const nanogui::Vector2i &p, int b, bool d,
                                   int m) {
  auto result = Button::mouseButtonEvent(p, b, d, m);
  if (!d && mPushed) {
    mPopup->raise();
  }

  return result;
}

void PopupButton::draw(NVGcontext *ctx) {
  if (!mEnabled && mPushed) mPushed = false;

  mPopup->setVisible(mPushed);
  Button::draw(ctx);

  if (mChevronIcon) {
    auto icon = utf8(mChevronIcon);
    NVGcolor textColor = mTextColor.w() == 0 ? mTheme->mTextColor : mTextColor;

    nvgFontSize(ctx,
                (mFontSize < 0 ? mTheme->mButtonFontSize : mFontSize) * 1.5f);
    nvgFontFace(ctx, "icons");
    nvgFillColor(ctx, mEnabled ? textColor : mTheme->mDisabledTextColor);
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);

    float iw = nvgTextBounds(ctx, 0, 0, icon.data(), nullptr, nullptr);
    Vector2f iconPos(mPos.x() + mSize.x() - iw - 8,
                     mPos.y() + mSize.y() * 0.5f - 1);

    nvgText(ctx, iconPos.x(), iconPos.y(), icon.data(), nullptr);
  }
}

void PopupButton::performLayout(NVGcontext *ctx) {
  Widget::performLayout(ctx);
  auto windowPos = window()->position();
  auto sz = this->size();
  sz.x() += 15 + windowPos.x();
  sz.y() /= 2;
  sz.y() += windowPos.y();

  mPopup->setAnchorPos(sz);
}

Popup::Popup(Widget *parent, Widget *widget)
    : Window(parent, ""),
      mWidget(widget),
      mAnchorPos(Vector2i::Zero()),
      mAnchorHeight(30) {
  requestFocus();
}

void Popup::raise() {
  Screen *screen = dynamic_cast<Screen *>(this->parent());
  if (screen) screen->moveWindowToFront(this);
  std::cout << "raise\n";
}

void Popup::performLayout(NVGcontext *ctx) {
  if (mLayout || mChildren.size() != 1) {
    Widget::performLayout(ctx);
  } else {
    mChildren[0]->setPosition(Vector2i::Zero());
    mChildren[0]->setSize(mSize);
    mChildren[0]->performLayout(ctx);
  }
}

void Popup::refreshRelativePlacement() {
  mVisible &= mParent->visibleRecursive();
  mPos = mWidget->position() + mAnchorPos + Vector2i(0, mAnchorHeight);
}

void Popup::draw(NVGcontext *ctx) {
  refreshRelativePlacement();

  if (!mVisible) return;

  int ds = mTheme->mWindowDropShadowSize, cr = mTheme->mWindowCornerRadius;

  /* Draw a drop shadow */
  NVGpaint shadowPaint =
      nvgBoxGradient(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr * 2,
                     ds * 2, mTheme->mDropShadow, mTheme->mTransparent);

  nvgBeginPath(ctx);
  nvgRect(ctx, mPos.x() - ds, mPos.y() - ds, mSize.x() + 2 * ds,
          mSize.y() + 2 * ds);
  nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);
  nvgPathWinding(ctx, NVG_HOLE);
  nvgFillPaint(ctx, shadowPaint);
  nvgFill(ctx);

  /* Draw window */
  nvgBeginPath(ctx);
  nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);

  nvgMoveTo(ctx, mPos.x() - 15, mPos.y() + mAnchorHeight);
  nvgLineTo(ctx, mPos.x() + 1, mPos.y() + mAnchorHeight - 15);
  nvgLineTo(ctx, mPos.x() + 1, mPos.y() + mAnchorHeight + 15);

  nvgFillColor(ctx, mTheme->mWindowPopup);
  nvgFill(ctx);
  nvgStrokeColor(ctx, mTheme->mBorderLight);
  nvgStroke(ctx);

  Widget::draw(ctx);
}
}
}
