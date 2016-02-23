#pragma once
#ifndef __APPLE_CC__
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#endif

namespace oa {
namespace geometry {
class Geometry {
 public:
  virtual uint32_t getIndexAmount() = 0;
  virtual void prepareOpenglBuffers() = 0;
  virtual void setupGeometry() = 0;
  virtual ~Geometry() {}
};
}
}
