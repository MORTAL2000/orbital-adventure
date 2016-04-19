#include <boost/filesystem.hpp>
#include <ctime>
#include <iostream>
#include "Planet.hpp"
#include "SolarSystem.hpp"
#include "Star.hpp"

namespace oa {
namespace game {
using namespace std::chrono;
using namespace std::chrono_literals;
const double SolarSystem::G = 6.67408e-11;
SolarSystem::SolarSystem() {
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

const render::Scene *SolarSystem::getScene() { return &scene; }

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
  auto momentInDays = getMoment(timePoint);
  for (auto &pair : celestialsMap) {
    auto &planet = pair.second;
    if (!planet->hasOrbit()) continue;
    auto &orbit = planet->getOrbit();
    auto &parentPlanet = celestialsMap[orbit.body];

    glm::vec3 position =
        planetPlaneCoordinates(planet->getOrbit(), momentInDays,
                               parentPlanet->getMass(), planet->getMass());
    std::cout << std::setprecision(15) << momentInDays << " "
              << planet->getName() << " " << glm::length(position) << "  "
              << orbit.semiMajorAxis << "\n";
    planet->setPosition(position);
  }
}
double SolarSystem::getMoment(int year, int month, int day,
                              uint32_t milliseconds) {
  year -= 2000;
  double d =
      367 * year - 7 * (year + (month + 9) / 12) / 4 + 275 * month / 9 + day;
  d += (double(milliseconds) / 1000 / 60 / 60) / 24;
  std::cout << std::setprecision(8) << d << " ";
  return d;
}

glm::vec3 SolarSystem::planetPlaneCoordinates(const Orbit &orbit, double moment,
                                              double Mass, double mass) {
  auto mu = G * (Mass + mass);
  auto e = orbit.eccentricity;
  auto e2 = e * e;
  double DAY = 60 * 60 * 24;
  double meanMotion = std::sqrt(mu / std::pow(orbit.semiMajorAxis, 3)) * DAY;
  double M = orbit.meanAnomaly + meanMotion * moment;
  double E = eccentricityAnomaly(e, M);
  double phi = trueAnomaly(e, E, 0.0);
  double R = orbit.semiMajorAxis * (1.0 - e2) / (1.0 + e * std::cos(phi));

  return glm::vec3(R * std::cos(phi), R * std::sin(phi), 0.0);
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
