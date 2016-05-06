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

  float size = glm::max(scale.z, glm::max(scale.x, scale.y)) * 1.0;
  float near, far;
  if (glm::length(accordingToCamera) < size * 4) {
    float toCenter = glm::length(accordingToCamera);
    float toSurface = toCenter - size;
    if (toSurface < 10e3) {
      near = 1;
      far = 1000e3;
    } else {
      near = toSurface / 2;
      far = toCenter + size;
    }
  } else {
    auto distance = glm::dot(glm::normalize(dir), accordingToCamera);
    float nearer = std::abs(distance - size) * 0.2f;  // one percent of distance
    near = std::max(0.01f, distance - size - nearer);
    far = distance + 0.3 * size;
  }
  auto newCamera = camera->changeClipping(near, far);

  auto &view = newCamera->getMatrix();
  auto &projection = newCamera->getProjectionMatrix();
  auto modelViewProjection = projection * view * mesh->getMatrix();
  holder->setUniformValue("modelViewProjection",
                          new Mat4OwnerUniform(modelViewProjection));
}
}
}
