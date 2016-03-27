#pragma once
#include "Mesh.hpp"
#include "ShaderManager.hpp"
#include "Geometry.hpp"
namespace oa {
namespace render {
class StarMesh : public Mesh {
  uint32_t programId;
  std::shared_ptr<geometry::Geometry> geometry;

 public:
  StarMesh();
  void render();
  void setupUniforms(glm::mat4, glm::mat4);
  uint32_t getProgramId();
};
}
}
