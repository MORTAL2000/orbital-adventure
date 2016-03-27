#include "GeometryManager.hpp"
#include "SphereGeometry.hpp"

namespace oa {
namespace render {
GeometryManager::GeometryManager() {}

std::shared_ptr<geometry::Geometry> GeometryManager::createSphereGeometry() {
  auto s =
      std::make_shared<geometry::SphereGeometry>(geometry::SphereGeometry());
  s->prepareOpenglBuffers();
  return s;
}
std::shared_ptr<geometry::Geometry> GeometryManager::loadGeometry(
    std::string geometryName) {
  if (geometryName == "SphereGeometry") {
    return createSphereGeometry();
  }
  // Return sphere geometry in any other case;
  return createSphereGeometry();
}
GeometryManager *GeometryManager::instance() {
  static GeometryManager inst;
  return &inst;
}
}
}
