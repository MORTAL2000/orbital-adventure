#pragma once
#include "Geometry.hpp"
namespace oa {
namespace geometry {
class PatchGeometry : public Geometry {
  GLuint geometryBuffer;
  void prepareOpenglBuffers();
  void setBuffers();
  void unsetBuffers();
  void render();
  uint32_t getIndexAmount();
};
}
}
