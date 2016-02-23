#include "ShaderManager.hpp"
namespace oa {
namespace render {
ShaderProgramManager::ShaderProgramManager() {}
ShaderProgramManager *ShaderProgramManager::instance() {
  static ShaderProgramManager inst;
  return &inst;
}
}
}
