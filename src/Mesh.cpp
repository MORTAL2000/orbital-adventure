#include "Mesh.hpp"
#include "Uniform.hpp"
#include <iostream>
namespace oa {
namespace render {
Mesh::Mesh(ShaderProgram *p, geometry::Geometry *g) : program(p), geometry(g) {
  setUniformValue("MVP", new Mat4Uniform(&modelViewProjection));
  setUniformValue("modelViewMatrix", new Mat4Uniform(&modelViewProjection));
}
uint32_t Mesh::getProgramId() { return program->getProgramId(); }

void Mesh::setUniformValue(std::string name, Uniform *u) {
  uniforms[name] = std::unique_ptr<Uniform>(u);
}
void Mesh::render() {
  geometry->setBuffers();
  geometry->render();
  geometry->unsetBuffers();
}
void Mesh::setupUniforms(glm::mat4 projection, glm::mat4 view) {
  modelViewProjection = projection * view * this->getMatrix();

  for (auto &pair : program->getUniformLocations()) {
    auto name = pair.first;
    auto location = pair.second;
    if (!uniforms.count(name)) {
      std::cerr << "No such uniform in mesh: " << name << "\n";
      continue;
    }
    uniforms[name]->setup(location);
  }
}
}
}
