#include "ShaderManager.hpp"
#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>
namespace oa {
namespace render {
ShaderProgramManager::ShaderProgramManager() {}

GLuint ShaderProgramManager::loadProgram(std::string vs, std::string fs) {
  std::cout << "GO compile shader!\n";
  std::cout << "vestex shader: " << vs << "\n";
  std::cout << "fragment shader: " << fs << "\n";

  std::ifstream vsf(vs);
  std::ifstream fsf(fs);
  std::string vshader((std::istreambuf_iterator<char>(vsf)),
                      std::istreambuf_iterator<char>());
  std::string fshader((std::istreambuf_iterator<char>(fsf)),
                      std::istreambuf_iterator<char>());
  GLuint vShaderId, fShaderId;
  vShaderId = glCreateShader(GL_VERTEX_SHADER);
  fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  GLint result = GL_FALSE;
  int infoLogLength;

  // vertex
  char const *VertexSourcePointer = vshader.c_str();
  glShaderSource(vShaderId, 1, &VertexSourcePointer, NULL);
  glCompileShader(vShaderId);
  glGetShaderiv(vShaderId, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(infoLogLength + 1);
    glGetShaderInfoLog(vShaderId, infoLogLength, NULL,
                       &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  // fragment

  char const *FragmentSourcePointer = fshader.c_str();
  glShaderSource(fShaderId, 1, &FragmentSourcePointer, NULL);
  glCompileShader(fShaderId);
  glGetShaderiv(fShaderId, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(infoLogLength + 1);
    glGetShaderInfoLog(fShaderId, infoLogLength, NULL,
                       &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }

  GLuint programId = glCreateProgram();
  glAttachShader(programId, vShaderId);
  glAttachShader(programId, fShaderId);
  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &result);
  glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> ProgramErrorMessage(infoLogLength + 1);
    glGetProgramInfoLog(programId, infoLogLength, NULL,
                        &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }
  glDeleteShader(fShaderId);
  glDeleteShader(vShaderId);
  return programId;
}

ShaderProgramManager *ShaderProgramManager::instance() {
  static ShaderProgramManager inst;
  return &inst;
}
}
}
