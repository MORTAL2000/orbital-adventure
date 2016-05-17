#pragma once
#include <map>
#include <regex>
#include "GLFWWrapper.hpp"
namespace oa {
namespace render {
class ShaderProgram {
  GLuint programId;
  std::map<std::string, std::string> uniformTypes;
  std::map<std::string, std::string> attributeTypes;
  std::map<std::string, GLuint> uniformLocations;
  std::map<std::string, std::string> fragmentOut;
  void parseShader(std::string shader);
  std::regex getAttributeRegex(int);
  std::regex getUniformRegex(int);
  std::regex getTargetsRegex(int);

  void setupUniformLocations();

 public:
  void compile(std::string vs, std::string fs);
  void compile(std::string vs, std::string fs, std::string gs);
  void compileFilter(std::string source, std::string fs);
  std::map<std::string, std::string>& getFragmentOutTypes();
  std::map<std::string, GLuint>& getUniformLocations();
  void free();
  GLuint getProgramId();
};
}
}
