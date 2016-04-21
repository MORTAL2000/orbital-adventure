#include "LanguageUtils.hpp"
#include "Mesh.hpp"
#include "Uniform.hpp"

namespace oa {
namespace render {
using namespace utils;
geometry::Geometry *Mesh::getGeometry() { return this->geometry; }
ShaderProgram *Mesh::getShader() { return program; }

Mesh::Mesh(ShaderProgram *p, geometry::Geometry *g) : program(p), geometry(g) {
  setUniformValue("MVP", new Mat4Uniform(&modelViewProjection));
  setUniformValue("modelViewMatrix", new Mat4Uniform(&modelViewProjection));
}
uint32_t Mesh::getProgramId() { return program->getProgramId(); }

void Mesh::prerender(const UniformHolder *) {}
void Mesh::setupUniforms(const Camera *camera) {
  auto &view = camera->getMatrix();
  auto &projection = camera->getProjectionMatrix();
  modelViewProjection = projection * view * this->getMatrix();

  for (auto &pair : program->getUniformLocations()) {
    auto name = pair.first;
    auto location = pair.second;
    setupUniform(name, location);
  }
}
}
}
