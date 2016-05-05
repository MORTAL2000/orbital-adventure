#include <glm/vec3.hpp>
#include "SkyboxGeometry.hpp"
namespace oa {
namespace geometry {
using namespace glm;
SkyboxGeometry::SkyboxGeometry() : size(1.0) {}
SkyboxGeometry::SkyboxGeometry(float s) : size(s) {}

uint32_t SkyboxGeometry::getIndexAmount() { return 0; }

void SkyboxGeometry::setBuffers() {
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void SkyboxGeometry::render() { glDrawArrays(GL_TRIANGLES, 0, 36); }
void SkyboxGeometry::unsetBuffers() { glDisableVertexAttribArray(0); }

void SkyboxGeometry::prepareOpenglBuffers() {
  vec3 SkyBoxVertices[36] = {
      vec3(1.0f, -1.0f, -1.0f),  vec3(1.0f, -1.0f, 1.0f),
      vec3(1.0f, 1.0f, 1.0f),    vec3(1.0f, 1.0f, 1.0f),
      vec3(1.0f, 1.0f, -1.0f),   vec3(1.0f, -1.0f, -1.0f),
      vec3(-1.0f, -1.0f, 1.0f),  vec3(-1.0f, -1.0f, -1.0f),
      vec3(-1.0f, 1.0f, -1.0f),  vec3(-1.0f, 1.0f, -1.0f),
      vec3(-1.0f, 1.0f, 1.0f),   vec3(-1.0f, -1.0f, 1.0f),
      vec3(-1.0f, 1.0f, -1.0f),  vec3(1.0f, 1.0f, -1.0f),
      vec3(1.0f, 1.0f, 1.0f),    vec3(1.0f, 1.0f, 1.0f),
      vec3(-1.0f, 1.0f, 1.0f),   vec3(-1.0f, 1.0f, -1.0f),
      vec3(-1.0f, -1.0f, 1.0f),  vec3(1.0f, -1.0f, 1.0f),
      vec3(1.0f, -1.0f, -1.0f),  vec3(1.0f, -1.0f, -1.0f),
      vec3(-1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f, 1.0f),
      vec3(1.0f, -1.0f, 1.0f),   vec3(-1.0f, -1.0f, 1.0f),
      vec3(-1.0f, 1.0f, 1.0f),   vec3(-1.0f, 1.0f, 1.0f),
      vec3(1.0f, 1.0f, 1.0f),    vec3(1.0f, -1.0f, 1.0f),
      vec3(-1.0f, -1.0f, -1.0f), vec3(1.0f, -1.0f, -1.0f),
      vec3(1.0f, 1.0f, -1.0f),   vec3(1.0f, 1.0f, -1.0f),
      vec3(-1.0f, 1.0f, -1.0f),  vec3(-1.0f, -1.0f, -1.0f)};
  for (int i = 0; i < 36; ++i) SkyBoxVertices[i] *= size;

  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 36, SkyBoxVertices,
               GL_STATIC_DRAW);
}
}
}
