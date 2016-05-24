#pragma once
#include "Mesh.hpp"
#include "UniformInstaller.hpp"
namespace oa {
namespace render {
class GeometryLODInstaller : public UniformInstaller {
  Mesh *mesh;
  glm::ivec2 texturesAmount;
  void install(UniformHolder *, const Camera *, double t);

 public:
  GeometryLODInstaller(Mesh *, glm::ivec2);
};
}
}
