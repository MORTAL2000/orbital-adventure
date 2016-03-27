#pragma once
#include "GLFWWrapper.hpp"
#include "Geometry.hpp"
#include <map>

namespace oa {
namespace render {
class GeometryManager {
  GeometryManager();
  std::map<std::string, std::shared_ptr<geometry::Geometry>> loadedGeometries;

 public:
  static GeometryManager *instance();
  std::shared_ptr<geometry::Geometry> loadGeometry(std::string geometryName);
  std::shared_ptr<geometry::Geometry> createSphereGeometry();
};
}
}
