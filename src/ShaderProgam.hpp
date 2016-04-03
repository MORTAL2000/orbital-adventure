#pragma once
#include <regex>
#include <map>
#include "GLFWWrapper.hpp"
namespace oa {
namespace render {
class ShaderProgram {
  GLuint programId;
  std::map<std::string, std::string> uniformTypes;
  std::map<std::string, std::string> attributeTypes;
  std::map<std::string, GLuint> uniformLocations;
  void parseShader(std::string shader);
  std::regex getAttributeRegex(int);
  std::regex getUniformRegex(int);

  void setupUniformLocations();

 public:
  void compile(std::string vs, std::string fs);
  std::map<std::string, GLuint> &getUniformLocations();
  void free();
  GLuint getProgramId();
};
}
}
