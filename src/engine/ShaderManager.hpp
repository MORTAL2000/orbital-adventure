#pragma once
#include <map>
#include "GLFWWrapper.hpp"
#include "ShaderProgam.hpp"

namespace oa {
namespace render {

class ShaderProgramManager {
  ShaderProgramManager();
  std::map<std::string, std::unique_ptr<ShaderProgram>> loadedPrograms;
  static const std::string filterVertexShader;

 public:
  ~ShaderProgramManager();
  static ShaderProgramManager *instance();
  ShaderProgram *loadProgram(std::string vertexShaderPath,
                             std::string fragmentShaderPath,
                             std::string geometryShaderPath);
  ShaderProgram *loadProgram(std::string fragmentShaderPath);
  ShaderProgram *loadProgram(std::string vertexShaderPath,
                             std::string fragmentShaderPath);
};
}
}
