#pragma once
#include "Mesh.hpp"
#include "ShaderManager.hpp"
namespace oa {
namespace render {
class StarMesh : public Mesh {
  uint32_t programId;

 public:
  StarMesh();
  uint32_t setupGeometry();
  void setupUniforms(glm::dmat4);
  uint32_t getProgramId();
};
}
}
