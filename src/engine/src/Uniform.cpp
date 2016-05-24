#include <iostream>
#include "Uniform.hpp"
namespace oa {
namespace render {

// Int owner
IntOwnerUniform::IntOwnerUniform(int f) : v(f) {}
void IntOwnerUniform::setup(GLuint l) { glUniform1i(l, v); }
Uniform* IntOwnerUniform::clone() { return new IntOwnerUniform(v); }

// float owner
FloatOwnerUniform::FloatOwnerUniform(float f) : v(f) {}
void FloatOwnerUniform::setup(GLuint l) { glUniform1f(l, v); }
Uniform* FloatOwnerUniform::clone() { return new FloatOwnerUniform(v); }

// ivec2 owner
IntVec2OwnerUniform::IntVec2OwnerUniform(glm::ivec2& v) : v2(v) {}
void IntVec2OwnerUniform::setup(GLuint location) {
  glUniform2iv(location, 1, &(v2[0]));
}
Uniform* IntVec2OwnerUniform::clone() { return new IntVec2OwnerUniform(v2); }

// vec3 owner
Vec3OwnerUniform::Vec3OwnerUniform(glm::vec3& v) : v3(v) {}
Vec3OwnerUniform::Vec3OwnerUniform(glm::vec3&& v) : v3(v) {}
void Vec3OwnerUniform::setup(GLuint location) {
  glUniform3fv(location, 1, &(v3[0]));
}
Uniform* Vec3OwnerUniform::clone() { return new Vec3OwnerUniform(v3); }

// vec2 owner
Vec2OwnerUniform::Vec2OwnerUniform(glm::vec2& v) : v2(v) {}
Vec2OwnerUniform::Vec2OwnerUniform(glm::vec2&& v) : v2(v) {}
void Vec2OwnerUniform::setup(GLuint location) {
  glUniform2fv(location, 1, &(v2[0]));
}
Uniform* Vec2OwnerUniform::clone() { return new Vec2OwnerUniform(v2); }

// mat4 owner
Mat4OwnerUniform::Mat4OwnerUniform(glm::mat4& m) : matrix(m) {}
void Mat4OwnerUniform::setup(GLuint location) {
  glUniformMatrix4fv(location, 1, GL_FALSE, &(matrix[0][0]));
}
Uniform* Mat4OwnerUniform::clone() { return new Mat4OwnerUniform(matrix); }

// mat4 ptr
Mat4Uniform::Mat4Uniform(glm::mat4* m) : matrix(m){};

void Mat4Uniform::setup(GLuint location) {
  glUniformMatrix4fv(location, 1, GL_FALSE, &(*matrix)[0][0]);
}
Uniform* Mat4Uniform::clone() { return new Mat4Uniform(matrix); }

// texture 3d ;
void Texture3DUniform::bindTexture(GLuint t) {
  glBindTexture(GL_TEXTURE_3D, t);
}
Texture3DUniform::Texture3DUniform(GLuint i) : TextureUniform(i) {}
Uniform* Texture3DUniform::clone() { return new Texture3DUniform(textureId); }

// texture 3d owner;
void Texture3DOwnerUniform::bindTexture(GLuint t) {
  glBindTexture(GL_TEXTURE_3D, t);
}
Texture3DOwnerUniform::Texture3DOwnerUniform(GLuint i) : TextureUniform(i) {}
Texture3DOwnerUniform::~Texture3DOwnerUniform() {
  glDeleteTextures(1, &textureId);
}
Uniform* Texture3DOwnerUniform::clone() {
  return new Texture3DUniform(textureId);  // prevent texture deletion
}

// texture owner
TextureOwnerUniform::TextureOwnerUniform(GLuint i) : TextureUniform(i) {}
TextureOwnerUniform::~TextureOwnerUniform() { glDeleteTextures(1, &textureId); }
Uniform* TextureOwnerUniform::clone() {
  return new TextureUniform(textureId);  // prevent deletion
}

// texture uniform
int TextureUniform::setupCounter = 0;
TextureUniform::TextureUniform(GLuint texture) : textureId(texture) {}

GLuint TextureUniform::textureIdGetter() { 
  return GL_TEXTURE0 + setupCounter; 
}

void TextureUniform::bindTexture(GLuint t) { glBindTexture(GL_TEXTURE_2D, t); }

void TextureUniform::setup(GLuint location) {
  glActiveTexture(textureIdGetter());
  bindTexture(textureId);
  glUniform1i(location, setupCounter);
  ++setupCounter;
  if (setupCounter > 31) setupCounter = 0;
}
Uniform* TextureUniform::clone() {
  return new TextureUniform(textureId);  // prevent deletion
}

// cubemap
CubemapUniform::CubemapUniform(GLuint t) : TextureUniform(t) {}
void CubemapUniform::bindTexture(GLuint t) {
  glBindTexture(GL_TEXTURE_CUBE_MAP, t);
}
Uniform* CubemapUniform::clone() { return new CubemapUniform(textureId); }
}
}
