#pragma once
#include "GLFWWrapper.hpp"
#include <map>

namespace oa {
namespace render {
class ShaderProgramManager {
  ShaderProgramManager();
  std::map<std::string, GLuint> loadedPrograms;

 public:
  static ShaderProgramManager *instance();
  GLuint loadProgram(std::string vertexShaderPath,
                     std::string fragmentShaderPath);
};
}
}
