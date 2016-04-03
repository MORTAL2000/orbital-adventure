#include "StarMesh.hpp"
#include "GeometryManager.hpp"
#include <iostream>
namespace oa {
namespace render {
StarMesh::StarMesh() {
  // geometry = GeometryManager::instance()->loadGeometry("SphereGeometry");
  // programId = ShaderProgramManager::instance()->loadProgram(
  //"../data/shaders/rockPlanetVertex.glsl",
  //"../data/shaders/rockPlanetFragment.glsl");
}

uint32_t StarMesh::getProgramId() { return programId; }
void StarMesh::setupUniforms(glm::mat4 projection, glm::mat4 view) {
  // auto mm = this->getMatrix();
  // auto m = projection * view * mm;
  // glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &m[0][0]);
}
void StarMesh::render() { geometry->render(); }
}
}
