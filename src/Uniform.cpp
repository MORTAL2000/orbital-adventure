#include "Uniform.hpp"
#include <iostream>
namespace oa {
namespace render {
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
