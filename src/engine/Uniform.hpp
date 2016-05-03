#pragma once
#include <glm/mat4x4.hpp>
#include "GLFWWrapper.hpp"
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

class IntVec2OwnerUniform : public Uniform {
  glm::ivec2 v2;
  void setup(GLuint);

 public:
  IntVec2OwnerUniform(glm::ivec2 &);
};
class Vec2OwnerUniform : public Uniform {
  glm::vec2 v2;
  void setup(GLuint);

 public:
  Vec2OwnerUniform(glm::vec2 &);
};

class Mat4OwnerUniform : public Uniform {
  glm::mat4 matrix;
  void setup(GLuint);

 public:
  Mat4OwnerUniform(glm::mat4 &);
};

class TextureUniform : public Uniform {
  static int setupCounter;
  GLuint textureId;
  void setup(GLuint);
  GLuint textureIdGetter();

 public:
  TextureUniform(GLuint);
};
}
}
