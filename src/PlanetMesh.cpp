#include "PlanetMesh.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "GeometryManager.hpp"
#include <iostream>

namespace oa {
namespace render {
uint32_t PlanetMesh::getProgramId() { return programId; }
PlanetMesh::PlanetMesh() {
  geometry = GeometryManager::instance()->loadGeometry("sphere");

  programId = ShaderProgramManager::instance()->loadProgram(
      "../data/shaders/rockPlanetVertex.glsl",
      "../data/shaders/rockPlanetFragment.glsl");
}
void PlanetMesh::setDiffuse(std::string fname) {
  diffuseMapId = TextureManager::instance()->loadTexture(fname);
}
void PlanetMesh::setSpecular(std::string fname) {
  specularMapId = TextureManager::instance()->loadTexture(fname);
}
void PlanetMesh::setNormal(std::string fname) {
  normalMapId = TextureManager::instance()->loadTexture(fname);
}

void PlanetMesh::setupUniforms(glm::dmat4 projectionViewMatrix) {
  std::cout << "setup uniforms\n";
}

uint32_t PlanetMesh::setupGeometry() {
  std::cout << "setup geometry\n";
  return this->geometry->getIndexAmount();
}
}
}
