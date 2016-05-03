#include "LODTextureManager.hpp"
#include "TextureManager.hpp"
#include <sstream>
#include <cmath>
namespace oa {
namespace render {
LODTextureManager::LODTextureManager(std::string root, int tw, int th,
                                     std::string ext)
    : root(root), totalWidth(tw), totalHeight(th), ext(ext) {
  for (size_t h = 0; h < totalHeight; ++h) {
    for (size_t w = 0; w < totalWidth; ++w) {
      std::stringstream ss;
      auto ix = w + h * totalWidth;
      ss << root << ix << "." << ext;
      paths[ix] = ss.str();
    }
  }
}
glm::ivec2 LODTextureManager::getDimensions() {
  return glm::ivec2(totalWidth, totalHeight);
}
TextureUniform *LODTextureManager::getTexture(int w, int h) {
  if (w < 0) w = (w + totalWidth) % totalWidth;
  if (h < 0) h = (h + totalHeight) % totalHeight;
  if (w >= totalWidth) w = (w - totalWidth);
  if (h >= totalWidth) h = (h - totalHeight);
  int ix = w + totalWidth * h;

  return new TextureUniform(TextureManager::instance()->loadTexture(paths[ix]));
}

glm::ivec2 LODTextureManager::getWH(const glm::vec2 &uv) {
  float widthStep = 1.0 / totalWidth;
  float heightStep = 1.0 / totalHeight;
  int w = std::floor(uv.x / widthStep);
  int h = std::floor(uv.y / heightStep);
  return glm::ivec2(w, h);
}
}
}
