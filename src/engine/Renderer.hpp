#pragma once
#include "Camera.hpp"
#include "GLFWWrapper.hpp"
#include "Scene.hpp"
namespace oa {
namespace render {
class Renderer {
 private:
 public:
  Renderer();
  void render(const Scene*, const Camera*);
};
}
}
