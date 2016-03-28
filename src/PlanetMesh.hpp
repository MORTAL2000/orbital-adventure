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

  GLuint mvpLocation;
  GLuint modelLocation;
  GLuint viewLocation;
  GLuint projectionlLocation;
  GLuint diffuseLocation;
  GLuint normalLocation;
  GLuint specularLocation;

 public:
  PlanetMesh();
  void setDiffuse(std::string);
  void setSpecular(std::string);
  void setNormal(std::string);
  void render();
  void setupUniforms(glm::mat4, glm::mat4);
  uint32_t getProgramId();
};
}
}
