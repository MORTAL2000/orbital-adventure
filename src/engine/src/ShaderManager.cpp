#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include "ShaderManager.hpp"
namespace oa {
namespace render {
const std::string ShaderProgramManager::filterVertexShader = R"(
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 projectionInverse;
uniform mat4 viewInverse;
uniform vec3 cameraPosition;
out vec3 rayVS;
out vec3 coordsVS;
out vec3 ray;
void main() {
  coordsVS = position;
  rayVS = normalize((viewInverse * vec4((projectionInverse * vec4(position, 0.0)).xy,-1.0, 0.0)).xyz);
  gl_Position = vec4(position, 1.0);
}
)";

ShaderProgramManager::ShaderProgramManager() {}

ShaderProgram *ShaderProgramManager::loadProgram(std::string fs) {
  std::string identity = fs;
  if (loadedPrograms.count(identity) > 0) {
    return loadedPrograms[identity].get();
  }
  ShaderProgram *sp = new ShaderProgram;
  sp->compileFilter(filterVertexShader, fs);
  loadedPrograms[identity] = std::unique_ptr<ShaderProgram>(sp);
  return sp;
}

ShaderProgram *ShaderProgramManager::loadProgram(std::string vs,
                                                 std::string fs) {
  std::string identity = vs + " :: " + fs;
  if (loadedPrograms.count(identity) > 0) {
    return loadedPrograms[identity].get();
  }
  ShaderProgram *sp = new ShaderProgram;
  sp->compile(vs, fs);
  loadedPrograms[identity] = std::unique_ptr<ShaderProgram>(sp);
  return sp;
}
ShaderProgram *ShaderProgramManager::loadProgram(std::string vs, std::string fs,
                                                 std::string gs) {
  std::string identity = vs + " :: " + fs + " :: " + gs;
  if (loadedPrograms.count(identity) > 0) {
    return loadedPrograms[identity].get();
  }
  ShaderProgram *sp = new ShaderProgram;
  sp->compile(vs, fs, gs);
  loadedPrograms[identity] = std::unique_ptr<ShaderProgram>(sp);
  return sp;
}

ShaderProgramManager::~ShaderProgramManager() {
  for (auto &pair : loadedPrograms) {
    pair.second->free();
  }
}

ShaderProgramManager *ShaderProgramManager::instance() {
  static ShaderProgramManager inst;
  return &inst;
}
}
}
