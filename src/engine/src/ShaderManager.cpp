#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include "ShaderManager.hpp"
namespace oa {
namespace render {
ShaderProgramManager::ShaderProgramManager() {}

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
