#pragma once
#include "Geometry.hpp"
namespace oa {
namespace geometry {
class SkyboxGeometry : public Geometry {
  float size;
  GLuint vertexBuffer;
  void setBuffers();
  void unsetBuffers();
  void render();
  uint32_t getIndexAmount();
  void prepareOpenglBuffers();
  void setupGeometry();

 public:
  SkyboxGeometry();
  SkyboxGeometry(float size);
};
}
}
