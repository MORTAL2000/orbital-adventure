#include <iostream>
#include "CurrentPlanetParams.hpp"
#include "engine/LanguageUtils.hpp"

namespace oa {
namespace game {
using namespace render;
using namespace utils;
void CurrentPlanetParams::install(UniformHolder *holder, const Camera *,
                                  double t) {
  float atmosphereHeight = 60;  // km
  float planetRadius = object->getSize();
  float HM = object->getHM();
  float HR = object->getHR();
  glm::vec3 betaMSca = object->getBetaMSca();
  glm::vec3 betaR = object->getBetaR();

  holder->setUniformValue("Rg", new FloatOwnerUniform(planetRadius * 1e-3));
  holder->setUniformValue(
      "Rt", new FloatOwnerUniform(planetRadius * 1e-3 + atmosphereHeight));
  holder->setUniformValue(
      "RL", new FloatOwnerUniform(planetRadius * 1e-3 + atmosphereHeight + 1));

  holder->setUniformValue("HM", new FloatOwnerUniform(HM));
  holder->setUniformValue("HR", new FloatOwnerUniform(HR));
  holder->setUniformValue("betaMSca", new Vec3OwnerUniform(betaMSca));
  holder->setUniformValue("betaR", new Vec3OwnerUniform(betaR));
}
CurrentPlanetParams::CurrentPlanetParams(const CelestialObject *ptr)
    : object(ptr) {}
}
}
