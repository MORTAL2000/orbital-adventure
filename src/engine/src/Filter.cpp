#include "Filter.hpp"
#include "GeometryManager.hpp"
#include "ShaderManager.hpp"
namespace oa {
namespace render {

std::vector<std::string> &Filter::getTargets() { return targets; }

void Filter::addUniformInstaller(UniformInstaller *ui) {
  uniformInstallers.push_back(std::unique_ptr<UniformInstaller>(ui));
}

void Filter::setupRenderingMode() {
  for (auto &f : glSettings) f();
}
GLuint Filter::getProgramId() { return shader->getProgramId(); }
geometry::Geometry *Filter::getGeometry() { return geometry; }
void Filter::updateUniforms() {
  for (auto &ui : uniformInstallers) ui->install(uniforms.get(), nullptr, 0);
  for (auto &u : shader->getUniformLocations()) {
    uniforms->setupUniform(u.first, u.second);
  }
}

void Filter::addGLSettings(std::function<void()> fn) {
  glSettings.push_back(fn);
}

Filter::Filter(std::string path) {
  uniforms.reset(new UniformOwner);
  shader = ShaderProgramManager::instance()->loadProgram(path);
  geometry = GeometryManager::instance()->createPatchGeometry();
  for (auto &p : shader->getFragmentOutTypes()) {
    targets.push_back(p.first);
  }
}
}
}
