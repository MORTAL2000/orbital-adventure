#include <iostream>
#include "IterativeTextureCreator.hpp"
namespace oa {
namespace render {
IterativeTextureCreator::IterativeTextureCreator(
    std::vector<TextureCreator *> creators, int count)
    : TextureCreator(nullptr, ""), creators(creators), count(count) {}

IterativeTextureCreator::FirstInstaller::FirstInstaller(bool *isFirst)
    : isFirst(isFirst) {}
void IterativeTextureCreator::FirstInstaller::install(UniformHolder *h,
                                                      const Camera *, double) {
  if (isFirst == nullptr) return;
  bool i = *isFirst;

  h->setUniformValue("first",
                     i ? new IntOwnerUniform(1) : new IntOwnerUniform(0));
}
void IterativeTextureCreator::render(const UniformHolder *user) {
  bool isFirst = true;
  auto fi = new FirstInstaller(&isFirst);

  for (int counter = 0; counter < count; ++counter) {
    for (auto creator : creators) {
      for (auto &ui : uniformInstallers) ui->install(creator, nullptr, 0);
      creator->addUniformInstaller(fi);
      creator->prepareFramebuffer(currentFramebuffer, textureHolder);
      creator->render(user);
      creator->cleanFramebuffer(currentFramebuffer);
    }
    isFirst = false;
  }
  fi->isFirst = nullptr;
}
void IterativeTextureCreator::prepareFramebuffer(GLuint fb,
                                                 UniformHolder *out) {
  currentFramebuffer = fb;
  textureHolder = out;
};
void IterativeTextureCreator::cleanFramebuffer(GLuint){};
}
}
