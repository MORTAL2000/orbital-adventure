#pragma once
#include "Geometry.hpp"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace oa {
namespace geometry {
class SphereGeometry : public Geometry {
  float radius;
  int segments;
  int rings;

  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvs;
  std::vector<uint32_t> indices;

  void createGeometry();

 public:
  uint32_t getIndexAmount();
  SphereGeometry(float radius = 0.1, int segments = 10, int rings = 10);
  void prepareOpenglBuffers();
  void setupGeometry();
};
}
}
