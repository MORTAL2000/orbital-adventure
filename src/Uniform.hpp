#pragma once
#include "GLFWWrapper.hpp"
#include <glm/mat4x4.hpp>
namespace oa {
namespace render {
class Uniform {
 public:
  virtual void setup(GLuint) = 0;
  virtual ~Uniform(){};
};

class Mat4Uniform : public Uniform {
  glm::mat4 *matrix;
  void setup(GLuint);

 public:
  Mat4Uniform(glm::mat4 *);
};
class TextureUniform : public Uniform {
  GLuint textureId;
  void setup(GLuint);

 public:
  TextureUniform(GLuint);
};
}
}
