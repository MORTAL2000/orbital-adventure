#pragma once
#include "Geometry.hpp"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace oa {
namespace geometry {
class SphereGeometry {
  float radius;
  int segments;
  int rings;
  GLuint positionsBufferId;
  GLuint normalsBufferId;
  GLuint uvsBufferId;
  GLuint indicesBufferId;

  std::vector<glm::dvec3> positions;
  std::vector<glm::dvec3> normals;
  std::vector<glm::dvec2> uvs;
  std::vector<glm::ivec3> indices;

  void createGeometry();

 public:
  uint32_t getIndexAmount();
  SphereGeometry(float radius = 1, int segments = 10, int rings = 10);
  void prepareOpenglBuffers();
  void setupGeometry();
};
}
}
