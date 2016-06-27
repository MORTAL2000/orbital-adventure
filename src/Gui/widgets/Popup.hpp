#pragma once
#include <nanogui/button.h>
#include <nanogui/entypo.h>
#include <nanogui/widget.h>
#include <nanogui/window.h>

namespace oa {
namespace gui {
class Popup : public nanogui::Window {
 public:
  /// Create a new popup parented to a screen (first argument) and a parent
  /// window
  Popup(nanogui::Widget *, nanogui::Widget *);

  /// Return the anchor position in the parent window; the placement of the
  /// popup is relative to it
  void setAnchorPos(const nanogui::Vector2i &anchorPos) {
    mAnchorPos = anchorPos;
  }
  Widget *getRoot();
  /// Set the anchor position in the parent window; the placement of the popup
  /// is relative to it
  const nanogui::Vector2i &anchorPos() const { return mAnchorPos; }

  /// Set the anchor height; this determines the vertical shift relative to the
  /// anchor position
  void setAnchorHeight(int anchorHeight) { mAnchorHeight = anchorHeight; }
  /// Return the anchor height; this determines the vertical shift relative to
  /// the anchor position
  int anchorHeight() const { return mAnchorHeight; }

  /// Invoke the associated layout generator to properly place child widgets, if
  /// any
  virtual void performLayout(NVGcontext *ctx) override;

  /// Draw the popup window
  virtual void draw(NVGcontext *ctx) override;
  void raise();

 protected:
  /// Internal helper function to maintain nested window position values
  virtual void refreshRelativePlacement() override;

 protected:
  nanogui::Widget *mWidget;
  nanogui::Vector2i mAnchorPos;
  int mAnchorHeight;
};

class PopupButton : public nanogui::Button {
 public:
  PopupButton(nanogui::Widget *parent, const std::string &caption = "Untitled",
              int buttonIcon = 0,
              int chevronIcon = ENTYPO_ICON_CHEVRON_SMALL_RIGHT);

  void setChevronIcon(int icon) { mChevronIcon = icon; }
  int chevronIcon() const { return mChevronIcon; }

  Popup *popup() { return mPopup; }
  const Popup *popup() const { return mPopup; }
  Widget *getRoot();

  virtual void draw(NVGcontext *ctx) override;
  virtual nanogui::Vector2i preferredSize(NVGcontext *ctx) const override;
  virtual void performLayout(NVGcontext *ctx) override;
  bool mouseButtonEvent(const nanogui::Vector2i &p, int b, bool d,
                        int m) override;
  bool focusEvent(bool focused) override;

 protected:
  Popup *mPopup;
  int mChevronIcon;
};
}
}
