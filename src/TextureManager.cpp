#include "TextureManager.hpp"

namespace oa {
namespace render {
TextureManager::TextureManager() {}
TextureManager* TextureManager::instance() {
  static TextureManager inst;
  return &inst;
}
}
}
