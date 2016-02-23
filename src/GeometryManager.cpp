#include "GeometryManager.hpp"

namespace oa {
namespace render {
GeometryManager::GeometryManager() {}
GeometryManager *GeometryManager::instance() {
  static GeometryManager inst;
  return &inst;
}
}
}
