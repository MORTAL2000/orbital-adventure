#include <iostream>
#include "CurrentPlanetAtmosphere.hpp"
#include "LanguageUtils.hpp"
namespace oa {
namespace game {
using namespace render;
using namespace utils;

CurrentPlanetAtmosphere::CurrentPlanetAtmosphere(
    const SolarSystem *ptr, const CelestialCameraManager *mgr)
    : solarSystem(ptr), cameraManager(mgr) {
  precalculatedTextures.push_back("inscatterSampler");
  precalculatedTextures.push_back("irradianceSampler");
  precalculatedTextures.push_back("transmittanceSampler");
  precalculatedTextures.push_back("deltaSMSampler");
  precalculatedTextures.push_back("deltaSRSampler");
  precalculatedTextures.push_back("deltaJSampler");
  precalculatedTextures.push_back("deltaESampler");
}

void CurrentPlanetAtmosphere::install(render::UniformHolder *holder,
                                      const render::Camera *, double) {
  auto object = solarSystem->getObjectOfInterest();
  const CelestialObject *sun = solarSystem->getSun();
  auto mesh = object->getMesh();
  glm::mat4 projectionInverse = glm::mat4(1.0);
  glm::mat4 viewInverse = glm::mat4(1.0);
  glm::vec3 pos(0.0);
  glm::vec3 sunToCameraDirection(0.0);

  if (cameraManager) {
    auto camera = cameraManager->getCamera();
    projectionInverse = glm::inverse(camera->getProjectionMatrix());
    viewInverse = glm::inverse(camera->getMatrix());
    pos = camera->getPosition();
    sunToCameraDirection = glm::normalize(sun->getMesh()->getPosition() - pos);
    pos *= 1e-3;
  } else {
    std::cerr << "camera manager is null\n";
  }

  float atmosphereHeight = 60;  // km
  float planetRadius = object->getSize();
  float HM = object->getHM();
  float HR = object->getHR();
  int RES_MU_S = 32, RES_R = 32, RES_NU = 8, RES_MU = 128;
  glm::vec3 betaMSca = object->getBetaMSca();
  glm::vec3 betaR = object->getBetaR();
  for (auto &t : precalculatedTextures) {
    Uniform *u = mesh->copy(t);
    if (u != nullptr) {
      holder->setUniformValue(t, u);
    }
  }

  holder->setUniformValue("Rg", new FloatOwnerUniform(planetRadius * 1e-3));
  holder->setUniformValue(
      "Rt", new FloatOwnerUniform(planetRadius * 1e-3 + atmosphereHeight));
  holder->setUniformValue("HM", new FloatOwnerUniform(HM));
  holder->setUniformValue("HR", new FloatOwnerUniform(HR));

  holder->setUniformValue(
      "RL", new FloatOwnerUniform(planetRadius * 1e-3 + atmosphereHeight + 1));
  holder->setUniformValue("projectionInverse",
                          new Mat4OwnerUniform(projectionInverse));
  holder->setUniformValue("viewInverse", new Mat4OwnerUniform(viewInverse));
  holder->setUniformValue("cameraPosition", new Vec3OwnerUniform(pos));

  holder->setUniformValue("RES_MU_S", new IntOwnerUniform(RES_MU_S));
  holder->setUniformValue("RES_MU", new IntOwnerUniform(RES_MU));
  holder->setUniformValue("RES_NU", new IntOwnerUniform(RES_NU));
  holder->setUniformValue("RES_R", new IntOwnerUniform(RES_R));
  holder->setUniformValue("betaMSca", new Vec3OwnerUniform(betaMSca));
  holder->setUniformValue("betaR", new Vec3OwnerUniform(betaR));
  holder->setUniformValue("sunDirection",
                          new Vec3OwnerUniform(sunToCameraDirection));
}
}
}
