#include <iostream>
#include "CurrentPlanetParams.hpp"

namespace oa {
namespace game {
using namespace render;
void CurrentPlanetParams::install(UniformHolder *holder, const Camera *,
                                  double t) {
  std::cout << "INSTALL UNIFORM FOR PLANET " << object->getName() << "\n";

  float atmosphereHeight = 60;  // km
  float planetRadius = object->getSize();
  holder->setUniformValue("Rg", new FloatOwnerUniform(planetRadius * 1e-3));
  holder->setUniformValue(
      "Rt", new FloatOwnerUniform(planetRadius * 1e-3 + atmosphereHeight));
  holder->setUniformValue(
      "RL", new FloatOwnerUniform(planetRadius * 1e-3 + atmosphereHeight + 1));
}
CurrentPlanetParams::CurrentPlanetParams(const CelestialObject *ptr)
    : object(ptr) {}
}
}
