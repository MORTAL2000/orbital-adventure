#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "GLFWWrapper.hpp"
namespace oa {
namespace render {
class Uniform {
 public:
  virtual void setup(GLuint) = 0;
  virtual Uniform* clone() = 0;
  virtual ~Uniform(){};
};

class Vec2Uniform : public Uniform {
  glm::vec2* v;
  void setup(GLuint);
  Uniform* clone();

 public:
  Vec2Uniform(glm::vec2*);
};

class Mat4Uniform : public Uniform {
  glm::mat4* matrix;
  void setup(GLuint);
  Uniform* clone();

 public:
  Mat4Uniform(glm::mat4*);
};

class IntVec2OwnerUniform : public Uniform {
  glm::ivec2 v2;
  void setup(GLuint);
  Uniform* clone();

 public:
  IntVec2OwnerUniform(glm::ivec2&);
};

class Vec3OwnerUniform : public Uniform {
  glm::vec3 v3;
  void setup(GLuint);
  Uniform* clone();

 public:
  Vec3OwnerUniform(glm::vec3&);
  Vec3OwnerUniform(glm::vec3&&);
};

class IntOwnerUniform : public Uniform {
  int v;
  void setup(GLuint);
  Uniform* clone();

 public:
  IntOwnerUniform(int);
};

class FloatOwnerUniform : public Uniform {
  float v;
  void setup(GLuint);
  Uniform* clone();

 public:
  FloatOwnerUniform(float);
};

class Vec2OwnerUniform : public Uniform {
  glm::vec2 v2;
  void setup(GLuint);
  Uniform* clone();

 public:
  Vec2OwnerUniform(glm::vec2&);
  Vec2OwnerUniform(glm::vec2&&);
};

class Mat4OwnerUniform : public Uniform {
  glm::mat4 matrix;
  void setup(GLuint);
  Uniform* clone();

 public:
  Mat4OwnerUniform(glm::mat4&);
};

class TextureUniform : public Uniform {
  static int setupCounter;
  void setup(GLuint);
  GLuint textureIdGetter();
  inline virtual void bindTexture(GLuint);
  virtual Uniform* clone();

 protected:
  GLuint textureId;

 public:
  TextureUniform(GLuint);
  virtual ~TextureUniform(){};
};

class TexturePtrUniform : public TextureUniform {
  GLuint* ptr;
  Uniform* clone();
  inline void bindTexture(GLuint);

 public:
  TexturePtrUniform(GLuint* ptr);
};

class Texture3DUniform : public TextureUniform {
  inline virtual void bindTexture(GLuint);
  virtual Uniform* clone();

 protected:
  GLuint textureId;

 public:
  Texture3DUniform(GLuint);
};

class TextureOwnerUniform : public TextureUniform {
  virtual Uniform* clone();

 public:
  TextureOwnerUniform(GLuint);
  ~TextureOwnerUniform();
};

class Texture3DOwnerUniform : public TextureUniform {
  inline void bindTexture(GLuint);
  virtual Uniform* clone();

 public:
  Texture3DOwnerUniform(GLuint);
  ~Texture3DOwnerUniform();
};

class CubemapUniform : public TextureUniform {
  inline void bindTexture(GLuint);
  Uniform* clone();

 public:
  CubemapUniform(GLuint);
};
}
}
