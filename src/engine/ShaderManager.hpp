#pragma once
#include "GLFWWrapper.hpp"
#include "ShaderProgam.hpp"
#include <map>

namespace oa {
namespace render {
class ShaderProgramManager {
  ShaderProgramManager();
  std::map<std::string, std::unique_ptr<ShaderProgram>> loadedPrograms;

 public:
  ~ShaderProgramManager();
  static ShaderProgramManager *instance();
  ShaderProgram *loadProgram(std::string vertexShaderPath,
                             std::string fragmentShaderPath);
};
}
}
