#include <iostream>
#include "GeometryLODInstaller.hpp"
#include "LanguageUtils.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
namespace oa {
namespace render {
using namespace utils;
GeometryLODInstaller::GeometryLODInstaller(Mesh *m, glm::ivec2 s)
    : mesh(m), texturesAmount(s) {}
void GeometryLODInstaller::install(UniformHolder *holder, const Camera *camera,
                                   double t) {
  auto position = camera->getPosition();
  auto direction = glm::normalize(mesh->getPosition() - position);
  float lat = 1.0f - acos(direction.z) / 1_pi;
  float lon =
      std::fmod(std::atan2(direction.y, direction.x) / (2_pi) + 1.0, 1.0);

  glm::vec2 texSize = 1.0f / glm::vec2(texturesAmount);
  glm::vec2 duv = glm::mod(glm::vec2(lon, lat), texSize);
  glm::vec2 tileCenter = glm::vec2(lon, lat) - duv + 0.5f * texSize;

  auto l = (1.0f - tileCenter.y) * 1_pi;
  direction.x = cos(tileCenter.x * 2_pi) * sin(l);
  direction.y = sin(tileCenter.x * 2_pi) * sin(l);
  direction.z = cos(l);

  glm::vec4 north = glm::vec4(0.0, 0.0, 1.0, 0.0);
  glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(north), direction));

  float angle = std::acos(
      glm::dot(glm::normalize(glm::vec3(north)), glm::normalize(direction)));
  glm::mat4 rotation = glm::rotate(angle, axis);

  holder->setUniformValue("northPoleToCameraRotation",
                          new render::Mat4OwnerUniform(rotation));
}
}
}
