#include <math.h>
#include <iostream>
#include "SphereGeometry.hpp"
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

void SphereGeometry::createGeometry() {
  std::vector<std::vector<uint32_t>> vertices;
  float const R = 1. / (float)(rings - 1);
  float const S = 1. / (float)(segments - 1);
  uint32_t index = 0;
  float heightSegments = rings;
  float widthSegments = segments;
  for (int y = 0; y <= heightSegments; ++y) {
    std::vector<uint32_t> rowIxes;
    float v = float(y) / heightSegments;
    for (int x = 0; x <= widthSegments; ++x) {
      float u = float(x) / widthSegments;
      float const px = -radius * cos(u * 2 * M_PI) * sin(v * M_PI);
      float const py = radius * cos(v * M_PI);
      float const pz = radius * sin(u * 2 * M_PI) * sin(v * M_PI);
      glm::vec3 n(px, py, pz);
      glm::vec3 p(px, py, pz);
      glm::vec2 uv(u, v);
      positions.push_back(p);
      normals.push_back(n);
      uvs.push_back(uv);
      rowIxes.push_back(index);
      ++index;
    }
    vertices.push_back(rowIxes);
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
