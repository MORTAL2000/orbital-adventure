#pragma once
namespace oa {
namespace gui {
struct View {
  virtual ~View(){};
  virtual void show() = 0;
  virtual void hide() = 0;
};
}
}
