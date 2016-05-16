#pragma once
#include "TextureCreator.hpp"
#include "UniformHolder.hpp"
namespace oa {
namespace render {
class IterativeTextureCreator : public TextureCreator {
  struct FirstInstaller : public UniformInstaller {
    bool *isFirst;
    void install(UniformHolder *, const Camera *, double) override;
    FirstInstaller(bool *isFirst);
  };

  std::vector<std::string> __mustbeEmptyTargets;
  UniformHolder *textureHolder;
  GLuint currentFramebuffer;
  std::vector<TextureCreator *> creators;
  int count;
  void render(const UniformHolder *h = nullptr) override;

  void prepareFramebuffer(GLuint, UniformHolder *out) override;
  void cleanFramebuffer(GLuint) override;

 public:
  IterativeTextureCreator(std::vector<TextureCreator *> creators, int count);
};
}
}
