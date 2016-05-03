#include "Mesh.hpp"
#pragma once
namespace oa {
namespace render {
class PersonalClippingMesh : public Mesh {
  void prerender(const UniformHolder *);
  void setupUniforms(const Camera *, double t);

 public:
  PersonalClippingMesh(ShaderProgram *sp, geometry::Geometry *);
};
}
}
