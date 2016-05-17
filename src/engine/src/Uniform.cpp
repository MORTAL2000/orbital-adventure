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
  // std::cout << "bind 3d\n";
  glBindTexture(GL_TEXTURE_3D, t);
}
Texture3DOwnerUniform::Texture3DOwnerUniform(GLuint i) : TextureUniform(i) {}
Texture3DOwnerUniform::~Texture3DOwnerUniform() {
  glDeleteTextures(1, &textureId);
}
Uniform* Texture3DOwnerUniform::clone() {
  return new TextureUniform(textureId);  // prevent texture deletion
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
  /*
  switch (setupCounter) {
    // clang-format off
    case 0: return GL_TEXTURE0;
    case 1: return GL_TEXTURE1;
    case 2: return GL_TEXTURE2;
    case 3: return GL_TEXTURE3;
    case 4: return GL_TEXTURE4;
    case 5: return GL_TEXTURE5;
    case 6: return GL_TEXTURE6;
    case 7: return GL_TEXTURE7;
    case 8: return GL_TEXTURE8;
    case 9: return GL_TEXTURE9;
    case 10: return GL_TEXTURE10;
    case 11: return GL_TEXTURE11;
    case 12: return GL_TEXTURE12;
    case 13: return GL_TEXTURE13;
    case 14: return GL_TEXTURE14;
    case 15: return GL_TEXTURE15;
    case 16: return GL_TEXTURE16;
    case 17: return GL_TEXTURE17;
    case 18: return GL_TEXTURE18;
    case 19: return GL_TEXTURE19;
    case 20: return GL_TEXTURE20;
    case 21: return GL_TEXTURE21;
    case 22: return GL_TEXTURE22;
    case 23: return GL_TEXTURE23;
    case 24: return GL_TEXTURE24;
    case 25: return GL_TEXTURE25;
    case 26: return GL_TEXTURE26;
    case 27: return GL_TEXTURE27;
    case 28: return GL_TEXTURE28;
    case 29: return GL_TEXTURE29;
    case 30: return GL_TEXTURE30;
    case 31: return GL_TEXTURE31;
    default :return GL_TEXTURE0;
      // clang-format on
  }*/
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
