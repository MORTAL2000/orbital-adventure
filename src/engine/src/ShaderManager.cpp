#include "ShaderManager.hpp"
#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>
namespace oa {
namespace render {
ShaderProgramManager::ShaderProgramManager() {}

ShaderProgram *ShaderProgramManager::loadProgram(std::string vs,
                                                 std::string fs) {
  std::string identity = vs + " :: " + fs;
  std::cout << "IDENTITY : " << identity << "\n";
  if (loadedPrograms.count(identity) > 0) {
    return loadedPrograms[identity].get();
  }
  ShaderProgram *sp = new ShaderProgram;
  sp->compile(vs, fs);
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
