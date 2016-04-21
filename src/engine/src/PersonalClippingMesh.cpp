#include <iostream>
#include "PersonalClippingMesh.hpp"

namespace oa {
namespace render {
PersonalClippingMesh::PersonalClippingMesh(ShaderProgram *sp,
                                           geometry::Geometry *g)
    : Mesh(sp, g) {}
void PersonalClippingMesh::prerender(const UniformHolder *) {}

void PersonalClippingMesh::setupUniforms(const Camera *camera) {
  Mesh::setupUniforms(camera);
}
}
}
