#include <iostream>
#include "PersonalClippingMesh.hpp"

namespace oa {
namespace render {
PersonalClippingMesh::PersonalClippingMesh(ShaderProgram *sp,
                                           geometry::Geometry *g)
    : Mesh(sp, g) {}
void PersonalClippingMesh::prerender(const UniformHolder *) {
  std::cout << "prerender";
}

void PersonalClippingMesh::setupUniforms(const Camera *camera) {
  std::cout << "setupUniforms";
  Mesh::setupUniforms(camera);
}
}
}
