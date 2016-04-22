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

void PersonalClippingMesh::setupUniforms(const Camera *camera) {
  auto scale = getScale();
  auto accordingToCamera = camera->getPosition() - getPosition();
  auto dir = camera->getDirection();

  auto distance = glm::dot(glm::normalize(dir), accordingToCamera);
  auto size = glm::max(scale.z, glm::max(scale.x, scale.y));
  auto near = distance - size;
  auto far = distance + size;
  auto newCamera = camera->changeClipping(near, far);
  Mesh::setupUniforms(newCamera);
}
}
}
