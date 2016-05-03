#include "PersonalClippingMatrixInstaller.hpp"
#include <iostream>
namespace oa {
namespace render {
PersonalClippingMatrixInstaller::PersonalClippingMatrixInstaller(Mesh *m)
    : mesh(m) {}
void PersonalClippingMatrixInstaller::install(UniformHolder *holder,
                                              const Camera *camera, double) {
  auto scale = mesh->getScale();
  auto accordingToCamera = camera->getPosition() - mesh->getPosition();
  auto dir = camera->getDirection();

  auto distance = glm::dot(glm::normalize(dir), accordingToCamera);
  auto size = glm::max(scale.z, glm::max(scale.x, scale.y));
  auto near = distance - size;
  auto far = distance + size;
  auto newCamera = camera->changeClipping(near, far);

  auto &view = newCamera->getMatrix();
  auto &projection = newCamera->getProjectionMatrix();
  auto modelViewProjection = projection * view * mesh->getMatrix();
  holder->setUniformValue("modelViewProjection",
                          new Mat4OwnerUniform(modelViewProjection));
}
}
}
