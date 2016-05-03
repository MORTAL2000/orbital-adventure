#pragma once
#include <map>
#include "Uniform.hpp"
#include <string>
namespace oa {
namespace render {
class LODTextureManager {
  int level;
  std::map<int, std::string> paths;
  std::string root;
  int totalWidth;
  int totalHeight;
  std::string ext;

 public:
  glm::ivec2 getWH(const glm::vec2 &uv);
  glm::ivec2 getDimensions();
  render::TextureUniform *getTexture(int w, int h);
  LODTextureManager(std::string root, int totalWidth, int totalHeight,
                    std::string ext);
};
}
}
