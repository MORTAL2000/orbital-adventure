#include "SkyboxUniformInstaller.hpp"

namespace oa {
namespace render {

SkyboxUniformInstaller::SkyboxUniformInstaller(float s) : skyboxSize(s) {}
void SkyboxUniformInstaller::install(UniformHolder *holder,
                                     const Camera *camera, double) {
  glm::vec3 cameraPosition = camera->getPosition();
  auto newCamera = camera->changeClipping(0.5 * skyboxSize, 2.0 * skyboxSize);
  auto &view = newCamera->getMatrix();
  auto &projection = newCamera->getProjectionMatrix();
  auto vp = projection * view;

  holder->setUniformValue("ViewProjectionMatrix", new Mat4OwnerUniform(vp));
  holder->setUniformValue("CameraPosition",
                          new Vec3OwnerUniform(cameraPosition));
}
}
}
