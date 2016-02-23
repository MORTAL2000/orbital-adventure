#pragma once
#include "Mesh.hpp"
#include "SphereGeometry.hpp"
namespace oa {
namespace render {
class PlanetMesh : public Mesh {
  std::shared_ptr<geometry::Geometry> geometry;
  uint32_t programId;
  GLuint diffuseMapId;
  GLuint specularMapId;
  GLuint normalMapId;

 public:
  PlanetMesh();
  void setDiffuse(std::string);
  void setSpecular(std::string);
  void setNormal(std::string);
  uint32_t setupGeometry();
  void setupUniforms(glm::dmat4);
  uint32_t getProgramId();
};
}
}
