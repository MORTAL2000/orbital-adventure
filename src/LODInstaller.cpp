#include "LanguageUtils.hpp"
#include "LODInstaller.hpp"
#include <glm/gtx/transform.hpp>
namespace oa {
namespace render {
using namespace utils;
LODInstaller::LODInstaller(const render::Mesh *m, LODTextureManager &&l)
    : mesh(m), lodManager(l) {}

void LODInstaller::install(render::UniformHolder *holder, const Camera *camera,
                           double) {
  auto position = camera->getPosition();
  auto direction = glm::normalize(mesh->getPosition() - position);
  glm::vec4 north = glm::vec4(0.0, 0.0, 1.0, 1.0);
  auto meshMatrix = mesh->getMatrix();
  auto cameraMatrix = camera->getMatrix();
  auto projectionMatrix = camera->getProjectionMatrix();
  direction = -direction;

  auto ang = std::fmod(std::asin(direction.z) / 1_pi + 1.5, 1.0);
  auto lon = std::fmod(atan2(direction.y, direction.x) / 2_pi + 1, 1);

  currentPosition = glm::vec2(lon, 1.0 - ang);
  glm::ivec2 wh = lodManager.getWH(currentPosition);
  glm::ivec2 dimension = lodManager.getDimensions();
   holder->setUniformValue("finest", lodManager.getTexture(wh[0], wh[1]));
  holder->setUniformValue("finestN", lodManager.getTexture(wh[0] - 1, wh[1]));
  holder->setUniformValue("finestS", lodManager.getTexture(wh[0] + 1, wh[1]));
  holder->setUniformValue("finestE", lodManager.getTexture(wh[0], wh[1] - 1));
  holder->setUniformValue("finestW", lodManager.getTexture(wh[0], wh[1] + 1));

  holder->setUniformValue("finestNE",
                          lodManager.getTexture(wh[0] - 1, wh[1] - 1));
  holder->setUniformValue("finestSE",
                          lodManager.getTexture(wh[0] + 1, wh[1] - 1));
  holder->setUniformValue("finestNW",
                          lodManager.getTexture(wh[0] - 1, wh[1] + 1));
  holder->setUniformValue("finestSW",
                          lodManager.getTexture(wh[0] + 1, wh[1] + 1));

  holder->setUniformValue("currentGridCenter",
                          new render::IntVec2OwnerUniform(wh));
  holder->setUniformValue("lodGridDimention",
                          new render::IntVec2OwnerUniform(dimension));
  holder->setUniformValue("currentCameraUV",
                          new render::Vec2OwnerUniform(currentPosition));
}
}
}
