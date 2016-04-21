#include <boost/filesystem.hpp>
#include <ctime>
#include <iostream>
#include "Planet.hpp"
#include "SolarSystem.hpp"
#include "Star.hpp"
#include "engine/LanguageUtils.hpp"

namespace oa {
namespace game {
using namespace std::chrono;
using namespace std::chrono_literals;
using namespace utils;
const double SolarSystem::G = 6.67408e-11;
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
  auto daysDiff = duration_cast<FloatDaysDuration>(timePoint - epoch2000);
  return daysDiff.count();
}

void SolarSystem::updatePlanets(system_clock::time_point &timePoint) {
  double momentInDays = getMoment(timePoint);
  for (auto &pair : celestialsMap) {
    auto &planet = pair.second;
    if (!planet->hasOrbit()) continue;
    auto &orbit = planet->getOrbit();
    auto &parentPlanet = celestialsMap[orbit.body];

    glm::dvec3 position =
        planetPlaneCoordinates(planet->getOrbit(), momentInDays,
                               parentPlanet->getMass(), planet->getMass());
    planet->setPosition(position);
  }
}

glm::dvec3 SolarSystem::planetPlaneCoordinates(const Orbit &orbit,
                                               double moment, double Mass,
                                               double mass) {
  double mu = G * (Mass + mass);
  auto e = orbit.eccentricity;
  auto e2 = e * e;
  double DAY = 60 * 60 * 24;
  double meanMotion =
      std::sqrt(mu / std::pow(orbit.semiMajorAxis, double(3))) * DAY;
  double M = std::fmod(orbit.meanAnomaly + meanMotion * moment, 2_pi);
  double E = eccentricityAnomaly(e, M);
  double phi = trueAnomaly(e, E, 0.0);
  double R = orbit.semiMajorAxis * (1.0 - e2) / (1.0 + e * std::cos(phi));

  return glm::dvec3(R * std::cos(phi), R * std::sin(phi), 0.0);
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
