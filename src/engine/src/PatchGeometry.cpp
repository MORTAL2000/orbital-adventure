#include <iostream>
#include "PatchGeometry.hpp"
namespace oa {
namespace geometry {

uint32_t PatchGeometry::getIndexAmount() { return 0; }
void PatchGeometry::prepareOpenglBuffers() {
  static const GLfloat verticies[] = {
      -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
      -1.0f, 1.0f,  0.0f, 1.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
  };
  glGenBuffers(1, &geometryBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, geometryBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, verticies,
               GL_STATIC_DRAW);
  std::cout << "Prepared patch geometry \n";
}
void PatchGeometry::render() {
  std::cout << "Render \n";
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
void PatchGeometry::unsetBuffers() { glDisableVertexAttribArray(0); }
void PatchGeometry::setBuffers() {
  std::cout << "Set up buffers \n";
  int attib = 0;
  glEnableVertexAttribArray(attib);
  glBindBuffer(GL_ARRAY_BUFFER, geometryBuffer);
  glVertexAttribPointer(attib, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}
}
}
