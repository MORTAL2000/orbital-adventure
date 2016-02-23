#include "StarMesh.hpp"
#include <iostream>
namespace oa {
namespace render {
StarMesh::StarMesh() {
  programId = ShaderProgramManager::instance()->loadProgram(
      "../data/shaders/rockPlanetVertex.glsl",
      "../data/shaders/rockPlanetFragment.glsl");
}

uint32_t StarMesh::getProgramId() { return programId; }
void StarMesh::setupUniforms(glm::dmat4 projectionView) {
  std::cout << "Start mesh uniforms"
            << "\n";
}
uint32_t StarMesh::setupGeometry() { return 0; }
}
}
