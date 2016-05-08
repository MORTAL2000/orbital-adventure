#include <iostream>
#include "GeometryLODInstaller.hpp"
#include "LanguageUtils.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
namespace oa {
namespace render {
using namespace utils;
GeometryLODInstaller::GeometryLODInstaller(Mesh *m) : mesh(m) {}
void GeometryLODInstaller::install(UniformHolder *holder, const Camera *camera,
                                   double t) {
  auto position = camera->getPosition();
  auto direction = glm::normalize(mesh->getPosition() - position);
  glm::vec4 north = glm::vec4(0.0, 0.0, 1.0, 0.0);
  glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(north), direction));
  float angle = std::acos(
      glm::dot(glm::normalize(glm::vec3(north)), glm::normalize(direction)));
  glm::mat4 rotation = glm::rotate(angle, axis);
  glm::mat4 irotation = glm::inverse(rotation);
  glm::mat4 viewMatrix = camera->getMatrix();
  glm::mat4 iViewMatrix = glm::inverse(viewMatrix);
  glm::vec3 pos, scale, skew;
  glm::vec4 pers;
  glm::quat rot;
  glm::decompose(viewMatrix, pos, rot, scale, skew, pers);
  glm::mat4 cameraRotation = glm::mat4_cast(rot);
  glm::mat4 iCameraRotation = glm::inverse(cameraRotation);
  holder->setUniformValue("inorthPoleToCameraRotation",
                          new render::Mat4OwnerUniform(irotation));
  holder->setUniformValue("northPoleToCameraRotation",
                          new render::Mat4OwnerUniform(rotation));
  holder->setUniformValue("viewMatrix",
                          new render::Mat4OwnerUniform(viewMatrix));
  holder->setUniformValue("iViewMatrix",
                          new render::Mat4OwnerUniform(iViewMatrix));
  holder->setUniformValue("iCameraRotation",
                          new render::Mat4OwnerUniform(iCameraRotation));
  holder->setUniformValue("cameraRotation",
                          new render::Mat4OwnerUniform(cameraRotation));
}
}
}
