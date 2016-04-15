#include <iostream>
#include "Geometry.hpp"
namespace oa {
namespace geometry {

void Geometry::render() {
  glDrawElements(GL_TRIANGLES, getIndexAmount(), GL_UNSIGNED_INT, (void*)0);
}
void Geometry::unsetBuffers() {
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}
void Geometry::setBuffers() {
  int attrib = -1;
  glEnableVertexAttribArray(++attrib);
  glBindBuffer(GL_ARRAY_BUFFER, positionsBufferId);
  glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glEnableVertexAttribArray(++attrib);
  glBindBuffer(GL_ARRAY_BUFFER, normalsBufferId);
  glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glEnableVertexAttribArray(++attrib);
  glBindBuffer(GL_ARRAY_BUFFER, uvsBufferId);
  glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
}
}
}
