#include <iostream>
#include "CustomGeometry.hpp"
namespace oa {
namespace geometry {
CustomGeometry::CustomGeometry() : hasIndex(false), trianglesInBuffer(0) {}

void CustomGeometry::setBuffers() {
  for (size_t i = 0; i < buffers.size(); ++i) {
    auto &b = buffers[i];
    glEnableVertexAttribArray(i);
    glBindBuffer(GL_ARRAY_BUFFER, b.id);
    glVertexAttribPointer(i, b.elementSize, b.dataType, GL_FALSE, 0, (void *)0);
  }
  if (hasIndex) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexId);
  }
}

void CustomGeometry::render() {
  if (hasIndex) {
    glDrawElements(GL_TRIANGLES, indexAmount, GL_UNSIGNED_INT, (void *)0);
  } else
    glDrawArrays(GL_TRIANGLES, 0, trianglesInBuffer);
}

void CustomGeometry::unsetBuffers() {
  for (size_t i = 0; i < buffers.size(); ++i) glDisableVertexAttribArray(i);
}

void CustomGeometry::addBuffer(char *data, int elements, int sizeOfElement,
                               int sizeOfType, int type) {
  buffer b;
  GLuint newBuffer;

  glGenBuffers(1, &newBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, newBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeOfType * sizeOfElement * elements, data,
               GL_STATIC_DRAW);
  b.id = newBuffer;
  b.dataType = type;
  b.elementSize = sizeOfElement;
  buffers.push_back(b);
  trianglesInBuffer = std::max(trianglesInBuffer, elements * sizeOfElement);
}

void CustomGeometry::addIndex(char *data, int elements, int sizeOfType) {
  glGenBuffers(1, &indexId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeOfType, data,
               GL_STATIC_DRAW);
  hasIndex = true;
  indexAmount = elements;
}
}
}
