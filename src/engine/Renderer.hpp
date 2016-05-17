#pragma once
#include "Camera.hpp"
#include "Filter.hpp"
#include "GLFWWrapper.hpp"
#include "Scene.hpp"
#include "TextureCreator.hpp"
#include "UniformHolder.hpp"

namespace oa {
namespace render {
class Renderer {
  struct RenderTargetsUniformInstaller : public UniformInstaller {
    std::map<std::string, GLuint> *map;
    bool *texturesUpdated;
    RenderTargetsUniformInstaller(std::map<std::string, GLuint> *, bool *,
                                  int *, int *);
    int *width, *height;
    void install(UniformHolder *, const Camera *, double);
  };
  GLuint framebuffer;
  GLuint depthbuffer;
  int width, height;
  bool texturesUpdated;
  std::vector<std::unique_ptr<Filter>> filters;
  // renderer owns all textures.
  std::map<std::string, GLuint> targets;
  std::string mainTarget = "mainRender";

  void createFrameBuffer(bool);
  void startFBORendering();
  void renderFilters();
  void unbindFramebuffer();

  void reinitFBOTargetTextures();
  void initFBOTargets(Filter *);
  void setupTarget(std::string &name);
  void bindTargets(std::vector<std::string> &&ts);
  void bindTargets(std::vector<std::string> &ts);
  void unbindTargets(int amount);
  // void bindTargets(std::vector<std::string> &);

 public:
  Renderer();
  void pushFilter(Filter *);
  void setViewportDimentions(int width, int height);
  void render(TextureCreator *, UniformHolder *);
  void render(const Scene *, const Camera *);
  void renderSorted(const Scene *, const Camera *);
  void clearColor();
  void clearDepth();
};
}
}
