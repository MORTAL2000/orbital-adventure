#pragma once
#include "UniformInstaller.hpp"
#include "Mesh.hpp"
namespace oa {
namespace render {
class PersonalClippingMatrixInstaller : public UniformInstaller {
  Mesh *mesh;
  void install(UniformHolder *, const Camera *, double t);

 public:
  PersonalClippingMatrixInstaller(Mesh *);
};
}
}
