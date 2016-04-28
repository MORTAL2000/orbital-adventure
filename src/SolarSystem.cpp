#include <boost/filesystem.hpp>
#include <ctime>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "CelestialCameraManager.hpp"
#include "Planet.hpp"
#include "SolarSystem.hpp"
#include "Star.hpp"
#include "engine/LanguageUtils.hpp"
#include "engine/UniformHolder.hpp"

namespace oa {
namespace game {
using namespace std::chrono;
using namespace std::chrono_literals;
using namespace utils;
const double SolarSystem::G = 6.67408e-11;

void SolarSystem::setupUniformUpdaters(
    const CelestialCameraManager *cameraMgr) {
  for (auto &pair : celestialsMap) {
    render::Mesh *mesh = pair.second->getMesh();
    auto updater = [mesh, cameraMgr](render::UniformHolder *holder, double) {
      auto position = cameraMgr->getCamera()->getPosition();
      auto direction = glm::normalize(mesh->getPosition() - position);
      glm::vec4 north = glm::vec4(0.0, 0.0, 1.0, 1.0);
      auto meshMatrix = mesh->getMatrix();
      auto cameraMatrix = cameraMgr->getCamera()->getMatrix();
      auto projectionMatrix = cameraMgr->getCamera()->getProjectionMatrix();
      north = cameraMatrix * north;
      glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(north), direction));
      float angle = std::acos(glm::dot(glm::normalize(glm::vec3(north)),
                                       glm::normalize(direction)));
      glm::mat4 rotation = glm::rotate(angle, axis);
      direction = -direction;

      auto ang = std::fmod(std::asin(direction.z) / 1_pi + 1.5, 1.0);
      auto lon = std::fmod(atan2(direction.y, direction.x) / 2_pi + 1, 1);

      // std::cout << "DIR " << ang << "\n";
      glm::vec2 currentPosition(lon, ang);
      // rotation = glm::translate(rotation, mesh->getPosition());
      holder->setUniformValue("viewMatrix",
                              new render::Mat4OwnerUniform(cameraMatrix));
      holder->setUniformValue("projectionMatrix",
                              new render::Mat4OwnerUniform(projectionMatrix));
      holder->setUniformValue("modelMatrix",
                              new render::Mat4OwnerUniform(meshMatrix));
      holder->setUniformValue("northPoleToCameraRotation",
                              new render::Mat4OwnerUniform(rotation));
      holder->setUniformValue("currentCameraUV",
                              new render::Vec2OwnerUniform(currentPosition));

    };
    mesh->addUniformUpdater(updater);
  }
}
SolarSystem::SolarSystem() : objectOfIntrest(nullptr) {
  std::tm time;
  time.tm_sec = 0;
  time.tm_min = 0;
  time.tm_hour = 0;
  time.tm_mday = 1;
  time.tm_mon = 0;
  time.tm_year = 100;
  time.tm_zone = "RU";
  time_t tm = mktime(&time);
  epoch2000 = system_clock::from_time_t(tm);
}

const CelestialObject *SolarSystem::getObjectOfInterest() {
  return objectOfIntrest;
}
void SolarSystem::setCurrentCelestial(const CelestialObject *ptr) {
  objectOfIntrest = ptr;
}

const render::Scene *SolarSystem::getScene() {
  if (!objectOfIntrest) return &scene;
  for (auto &p : celestialsMap) p.second->updateMesh(objectOfIntrest);
  return &scene;
}

inline float random() { return float(std::rand()) / (std::pow(2, 32) / 2); }

const std::map<PlanetID, CelestialPtr> &SolarSystem::getPlanetMap() const {
  return this->celestialsMap;
}

void SolarSystem::addPlanet(CelestialPtr planet) {
  PlanetID id(planet->getName());

  scene.addMesh(planet->getMesh());
  celestialsMap.insert(std::make_pair(id, std::move(planet)));
}
double SolarSystem::getMoment(system_clock::time_point &timePoint) {
  return duration_cast<FloatDuration>(timePoint - epoch2000).count();
}

void SolarSystem::updatePlanets(system_clock::time_point &timePoint) {
  double momentInDays = getMoment(timePoint);
  for (auto &pair : celestialsMap) {
    auto &planet = pair.second;
    if (!planet->hasOrbit()) {
      continue;
    }
    auto &orbit = planet->getOrbit();
    auto &parentPlanet = celestialsMap[orbit.body];

    glm::dvec3 position =
        planetPlaneCoordinates(planet->getOrbit(), momentInDays,
                               parentPlanet->getMass(), planet->getMass());

    planet->setPosition(position + parentPlanet->getPosition());
    planet->getMesh()->updateUniforms(momentInDays);
  }
}

glm::dvec3 SolarSystem::planetPlaneCoordinates(const Orbit &orbit,
                                               double moment, double Mass,
                                               double mass) {
  double mu = G * (Mass + mass);
  auto e = orbit.eccentricity;
  auto e2 = e * e;
  double DAY = 60 * 60 * 24;
  double meanMotion = std::sqrt(mu / std::pow(orbit.semiMajorAxis, double(3)));
  double M = orbit.meanAnomaly + meanMotion * moment;
  double E = eccentricityAnomaly(e, M);
  double phi = trueAnomaly(e, E, 0.0);
  double R = orbit.semiMajorAxis * (1.0 - e2) / (1.0 + e * std::cos(phi));
  double N = orbit.longitudeOfAscendingNode;
  double w = orbit.argumentOfPeriapsis;
  double v = phi;
  double i = orbit.inclination;

  double x = R * (cos(N) * cos(v + w) - sin(N) * sin(v + w) * cos(i));
  double y = R * (sin(N) * cos(v + w) + cos(N) * sin(v + w) * cos(i));
  double z = R * (sin(v + w) * sin(i));

  return glm::dvec3(x, y, z);
}

double SolarSystem::eccentricityAnomaly(double eccentricity, double M) {
  double En = 1.0;
  double Eo = 0.0;
  double Et = 0.0;
  while (std::abs(En - Eo) > 0.0000001) {
    Et = En;
    En = M + eccentricity * std::sin(Eo);
    Eo = Et;
  }
  return En;
}

double SolarSystem::trueAnomaly(double eccentricity, double E, double) {
  double S = std::sin(E);
  double C = std::cos(E);
  double fak = std::sqrt(1.0 - eccentricity * eccentricity);
  double phi = std::atan2(fak * S, C - eccentricity);
  return phi;
}
}
}
