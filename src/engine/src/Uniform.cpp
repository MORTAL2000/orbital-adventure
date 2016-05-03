#include <iostream>
#include "Uniform.hpp"
namespace oa {
namespace render {
IntVec2OwnerUniform::IntVec2OwnerUniform(glm::ivec2& v) : v2(v) {}
void IntVec2OwnerUniform::setup(GLuint location) {
  glUniform2iv(location, 1, &(v2[0]));
}

Vec2OwnerUniform::Vec2OwnerUniform(glm::vec2& v) : v2(v) {}
void Vec2OwnerUniform::setup(GLuint location) {
  glUniform2fv(location, 1, &(v2[0]));
}

Mat4OwnerUniform::Mat4OwnerUniform(glm::mat4& m) : matrix(m) {}
void Mat4OwnerUniform::setup(GLuint location) {
  glUniformMatrix4fv(location, 1, GL_FALSE, &(matrix[0][0]));
}

Mat4Uniform::Mat4Uniform(glm::mat4* m) : matrix(m){};

void Mat4Uniform::setup(GLuint location) {
  glUniformMatrix4fv(location, 1, GL_FALSE, &(*matrix)[0][0]);
}

int TextureUniform::setupCounter = 0;
TextureUniform::TextureUniform(GLuint texture) : textureId(texture) {}

GLuint TextureUniform::textureIdGetter() {
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
  }
}

void TextureUniform::setup(GLuint location) {
  glActiveTexture(textureIdGetter());
  glBindTexture(GL_TEXTURE_2D, textureId);
  glUniform1i(location, setupCounter);
  ++setupCounter;
  if (setupCounter > 31) setupCounter = 0;
}
}
}
