#include <math.h>
#include <iostream>
#include "LanguageUtils.hpp"
#include "PlanetGeometry.hpp"

namespace oa {
namespace geometry {
using namespace utils;
PlanetGeometry::PlanetGeometry(float r, int s, int rings)
    : radius(r), segments(s), rings(rings) {}

uint32_t PlanetGeometry::getIndexAmount() { return indices.size(); }

void PlanetGeometry::prepareOpenglBuffers() {
  createGeometry();
  GLuint buffers[4];

  glGenBuffers(4, buffers);
  positionsBufferId = buffers[0];
  normalsBufferId = buffers[1];
  uvsBufferId = buffers[2];
  indicesBufferId = buffers[3];

  glBindBuffer(GL_ARRAY_BUFFER, positionsBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * positions.size(),
               &positions[0][0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, normalsBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * normals.size(),
               &normals[0][0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, uvsBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * uvs.size(), &uvs[0][0],
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(),
               &indices[0], GL_STATIC_DRAW);
}

void PlanetGeometry::createGeometry() {
  std::vector<std::vector<uint32_t>> vertices;
  float const R = 1. / (float)(rings - 1);
  float const S = 1. / (float)(segments - 1);
  uint32_t index = 0;
  float widthSegments = segments;
  rings = 0;
  double baseStep = 1e-3;
  double step = baseStep;
  ;

  for (double v = 0;; v += step) {
    if (v < 0.125_pi) step = baseStep;
    if (v > 0.125_pi && v < 0.25_pi) step = 2 * baseStep;
    if (v > 0.25_pi && v < 0.5_pi) step = 4 * baseStep;

    std::cout << "STEP " << step << "\n";
    std::vector<uint32_t> rowIxes;
    for (int x = 0; x <= widthSegments; ++x) {
      float u = float(x) / widthSegments;
      float const px = radius * cos(u * 2 * M_PI) * sin(v);
      float const py = radius * sin(u * 2 * M_PI) * sin(v);
      float const pz = radius * cos(v);
      glm::vec3 n(px, py, pz);
      glm::vec3 p(px, py, pz);
      glm::vec2 uv(u, 1.0 - v);
      positions.push_back(p);
      normals.push_back(n);
      uvs.push_back(uv);
      rowIxes.push_back(index);
      ++index;
    }
    vertices.push_back(rowIxes);
    if (v > 1_pi) break;
    ++rings;
  }

  for (int r = 0; r < rings; ++r) {
    for (int s = 0; s < segments; ++s) {
      auto v1 = vertices[r][s + 1];
      auto v2 = vertices[r][s];
      auto v3 = vertices[r + 1][s];
      auto v4 = vertices[r + 1][s + 1];
      if (r != 0) {
        indices.push_back(v1);
        indices.push_back(v2);
        indices.push_back(v4);
      }
      if (r != rings - 1) {
        indices.push_back(v2);
        indices.push_back(v3);
        indices.push_back(v4);
      }
    }
  }
}
}
}
