#include "GeometryManager.hpp"
#include "SkyboxGeometry.hpp"
#include "SphereGeometry.hpp"

namespace oa {
namespace render {
using namespace boost::property_tree;
GeometryManager::GeometryManager() {}

geometry::Geometry *GeometryManager::createSkyboxGeometry(float size) {
  geometry::Geometry *ss = new geometry::SkyboxGeometry(size);
  ss->prepareOpenglBuffers();
  return ss;
}

geometry::Geometry *GeometryManager::createSphereGeometry(double radius,
                                                          int rings,
                                                          int segments) {
  geometry::SphereGeometry *s =
      new geometry::SphereGeometry(radius, segments, rings);
  s->prepareOpenglBuffers();
  return s;
}
geometry::Geometry *GeometryManager::loadGeometry(ptree &geometryProps) {
  std::string geometryName = geometryProps.get("name", "no name");
  ptree options = geometryProps.get_child("options");

  if (geometryName == "SphereGeometry") {
    int rings = options.get<int>("rings", 10);
    int segments = options.get<int>("segments", 10);
    double radius = options.get<double>("radius", 1.f);
    return createSphereGeometry(radius, rings, segments);
  }
  return createSphereGeometry();
}

GeometryManager *GeometryManager::instance() {
  static GeometryManager inst;
  return &inst;
}
}
}
