#include "GeometryLODInstaller.hpp"
#include <glm/gtx/transform.hpp>
namespace oa {
namespace render {
GeometryLODInstaller::GeometryLODInstaller(Mesh *m) : mesh(m) {}
void GeometryLODInstaller::install(UniformHolder *holder, const Camera *camera,
                                   double t) {
  auto position = camera->getPosition();
  auto direction = glm::normalize(mesh->getPosition() - position);
  glm::vec4 north = glm::vec4(0.0, 0.0, 1.0, 1.0);
  glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(north), direction));
  float angle = std::acos(
      glm::dot(glm::normalize(glm::vec3(north)), glm::normalize(direction)));
  glm::mat4 rotation = glm::rotate(angle, axis);
  holder->setUniformValue("northPoleToCameraRotation",
                          new render::Mat4OwnerUniform(rotation));
}
}
}
