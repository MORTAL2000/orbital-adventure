#pragma once
#include "Geometry.hpp"
namespace oa {
namespace geometry {
class CustomGeometry : public Geometry {
  struct buffer {
    GLuint id;
    int dataType;
    int elementSize;
  };

  std::vector<buffer> buffers;
  bool hasIndex;
  GLuint indexId;
  int indexAmount;
  int trianglesInBuffer;

  void setBuffers();
  void unsetBuffers();
  void render();
  uint32_t getIndexAmount() { return 0; }
  void prepareOpenglBuffers(){};

 public:
  void addBuffer(char *, int elements, int sizeOfElement, int typeOfElement,
                 int type = GL_FLOAT);
  void addIndex(char *, int numIndex, int);
  CustomGeometry();
};
}
}
