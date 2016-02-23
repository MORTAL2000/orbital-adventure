#include "SphereGeometry.hpp"
#include <math.h>
#include <iostream>
namespace oa {
namespace geometry {
SphereGeometry::SphereGeometry(float r, int s, int rings)
    : radius(r), segments(s), rings(rings) {}

uint32_t SphereGeometry::getIndexAmount() { return indices.size(); }

void SphereGeometry::setupGeometry() {
  int attribLocation = 0;
  glEnableVertexAttribArray(++attribLocation);
  glBindBuffer(GL_ARRAY_BUFFER, positionsBufferId);
  glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glEnableVertexAttribArray(++attribLocation);
  glBindBuffer(GL_ARRAY_BUFFER, normalsBufferId);
  glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glEnableVertexAttribArray(++attribLocation);
  glBindBuffer(GL_ARRAY_BUFFER, uvsBufferId);
  glVertexAttribPointer(attribLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, positionsBufferId);
}

void SphereGeometry::prepareOpenglBuffers() {
  createGeometry();
  GLuint buffers[] = {positionsBufferId, normalsBufferId, uvsBufferId,
                      indicesBufferId};
  glGenBuffers(4, buffers);
  glBindBuffer(GL_ARRAY_BUFFER, positionsBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * 3 * positions.size(),
               &positions.at(0), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, normalsBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * 3 * normals.size(),
               &normals.at(0), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, uvsBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * 2 * uvs.size(), &uvs.at(0),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * positions.size(),
               &indices.at(0), GL_STATIC_DRAW);
}

void SphereGeometry::createGeometry() {
  std::cout << M_PI_2 << "\n";
  std::vector<std::vector<uint32_t>> vertices;
  float const R = 1. / (float)(rings - 1);
  float const S = 1. / (float)(segments - 1);
  uint32_t index = 0;
  for (int r = 0; r <= rings; ++r) {
    std::vector<uint32_t> rowIxes;
    for (int s = 0; s <= segments; ++s) {
      float const y = sin(-M_PI_2 + M_PI * r * R);
      float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
      float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);
      glm::dvec3 n(x, y, z);
      glm::dvec3 p(x * radius, y * radius, z * radius);
      glm::dvec2 uv(r * R, s * S);
      positions.push_back(p);
      normals.push_back(n);
      uvs.push_back(uv);
      rowIxes.push_back(index++);
    }
    vertices.push_back(rowIxes);
  }
  for (int r = 0; r < rings; ++r) {
    for (int s = 0; s < segments; ++s) {
      auto v1 = vertices[r][s + 1];
      auto v2 = vertices[r][s];
      auto v3 = vertices[r + 1][s];
      auto v4 = vertices[r + 1][s + 1];
      if (r != 0) indices.push_back(glm::vec3(v1, v2, v4));
      if (r != rings - 1) indices.push_back(glm::vec3(v2, v3, v4));
    }
  }
}
}
}
