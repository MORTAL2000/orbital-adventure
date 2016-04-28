#include <iostream>
#include "Uniform.hpp"
namespace oa {
namespace render {
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

TextureUniform::TextureUniform(GLuint texture) : textureId(texture) {}

void TextureUniform::setup(GLuint location) {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glUniform1i(location, 0);
}
}
}
