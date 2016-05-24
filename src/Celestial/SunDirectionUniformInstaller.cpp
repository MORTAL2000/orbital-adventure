#include "SunDirectionUniformInstaller.hpp"

namespace oa {
namespace game {
SunDirectionUniformInstaller::SunDirectionUniformInstaller(render::Mesh *s,
                                                           render::Mesh *m)
    : sun(s), me(m) {}
void SunDirectionUniformInstaller::install(render::UniformHolder *holder,
                                           const render::Camera *, double t) {
  glm::vec3 direction = glm::normalize(sun->getPosition() - me->getPosition());
  holder->setUniformValue("sunDirection",
                          new render::Vec3OwnerUniform(direction));
}
}
}
