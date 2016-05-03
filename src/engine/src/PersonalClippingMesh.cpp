#include <glm/gtc/matrix_inverse.hpp>
#include <iostream>
#include "LanguageUtils.hpp"
#include "PersonalClippingMesh.hpp"

namespace oa {
namespace render {
using namespace utils;
PersonalClippingMesh::PersonalClippingMesh(ShaderProgram *sp,
                                           geometry::Geometry *g)
    : Mesh(sp, g) {}
void PersonalClippingMesh::prerender(const UniformHolder *) {
  glClear(GL_DEPTH_BUFFER_BIT);
}

void PersonalClippingMesh::setupUniforms(const Camera *camera, double t) {
  Mesh::setupUniforms(camera, t);
}
}
}
