#include <iostream>
#include "LanguageUtils.hpp"
#include "PersonalClippingMatrixInstaller.hpp"
namespace oa {
namespace render {
using namespace utils;
PersonalClippingMatrixInstaller::PersonalClippingMatrixInstaller(Mesh *m)
    : mesh(m) {}
void PersonalClippingMatrixInstaller::install(UniformHolder *holder,
                                              const Camera *camera, double) {
  auto scale = mesh->getScale();
  auto accordingToCamera = camera->getPosition() - mesh->getPosition();
  auto dir = camera->getDirection();

  auto distance = glm::dot(glm::normalize(dir), accordingToCamera);
  float size = glm::max(scale.z, glm::max(scale.x, scale.y)) * 1.0;
  float nearer = std::abs(distance - size) * 0.1f;  // one percent of distance
  auto near = std::max(0.01f, distance - size - nearer);
  auto far = distance;
  auto newCamera = camera->changeClipping(near, far);

  auto &view = newCamera->getMatrix();
  auto &projection = newCamera->getProjectionMatrix();
  auto modelViewProjection = projection * view * mesh->getMatrix();
  holder->setUniformValue("modelViewProjection",
                          new Mat4OwnerUniform(modelViewProjection));
}
}
}
