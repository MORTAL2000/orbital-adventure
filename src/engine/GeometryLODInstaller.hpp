#pragma once
#include "UniformInstaller.hpp"
#include "Mesh.hpp"
namespace oa {
namespace render {
class GeometryLODInstaller : public UniformInstaller {
  Mesh *mesh;
  void install(UniformHolder *, const Camera *, double t);

 public:
  GeometryLODInstaller(Mesh *);
};
}
}
