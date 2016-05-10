#pragma once
#include "Camera.hpp"
#include "GLFWWrapper.hpp"
#include "Scene.hpp"
#include "TextureCreator.hpp"
#include "UniformHolder.hpp"
namespace oa {
namespace render {
class Renderer {
 private:
  GLuint framebuffer;
  GLuint depthbuffer;

  void createFrameBuffer(bool);

 public:
  Renderer();
  void render(TextureCreator *, UniformHolder *);
  void render(const Scene *, const Camera *);
  void renderSorted(const Scene *, const Camera *);
  void clearColor();
  void clearDepth();
};
}
}
