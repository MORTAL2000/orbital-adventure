#include <iostream>
#include "Planet.hpp"
#include "SolarSystemCreator.hpp"
#include "Star.hpp"
#include "engine/LanguageUtils.hpp"

namespace oa {
namespace game {
using namespace utils;

SolarSystemCreator::SolarSystemCreator() : solarSystem(new SolarSystem) {}
std::unique_ptr<SolarSystem> SolarSystemCreator::getSolarSystem() {
  return std::move(solarSystem);
}
void SolarSystemCreator::setupUniformUpdaters(
    const CelestialCameraManager *cameraMgr) {}
void SolarSystemCreator::createSolarSystem(std::string filepath) {
  meshFabric.setRootDir(filepath);
  using boost::property_tree::ptree;
  ptree planetsTree;
  read_json(filepath, planetsTree);
  for (auto &v : planetsTree) parsePlanet(v);
}
void SolarSystemCreator::parsePlanet(
    boost::property_tree::ptree::value_type &value) {
  auto tree = value.second;
  std::string name = tree.get<std::string>("name");
  PlanetID id(name);
  bool isStar = tree.get("isStar", false);
  double mass = tree.get<double>("mass");
  double radius = tree.get<double>("radius");
  if (isStar) {
    boost::property_tree::ptree meshProps = tree.get_child("mesh");
    auto star = CelestialPtr(new Star(mass, radius, name));
    auto mesh = meshFabric.createMesh(meshProps);
    star->setMesh(mesh);
    solarSystem->addPlanet(std::move(star));
    return;
  }
  auto meanAnomaly = tree.get_optional<double>("meanAnomaly");
  auto meanLongitude = tree.get_optional<double>("meanLongitude");
  auto longitudeOfPeriapsis = tree.get_optional<double>("longitudeOfPeriapsis");
  double longitudeOfAscendingNode =
      tree.get<double>("longitudeOfAscendingNode");
  double argumentOfPeriapsis = tree.get<double>("argumentOfPeriapsis");
  double inclination = tree.get<double>("inclination");
  double eccentricity = tree.get<double>("eccentricity");
  double semiMajorAxis = tree.get<double>("semiMajorAxis");
  double surfacePressure = tree.get<double>("surfacePressure");
  std::string parentName = tree.get<std::string>("orbitOn");
  double meanAnomalyAtJ200 = 0;
  if (meanAnomaly)
    meanAnomalyAtJ200 = *meanAnomaly;
  else {
    if (meanLongitude && longitudeOfPeriapsis) {
      meanAnomalyAtJ200 = *meanLongitude - *longitudeOfPeriapsis;
    } else {
      if (!meanLongitude) std::cout << "no meanLongitude\n";
      if (!longitudeOfPeriapsis) std::cout << "no longitudeOfPeriapsis\n";
    }
  }
  meanAnomalyAtJ200 = glm::radians(meanAnomalyAtJ200);
  while (meanAnomalyAtJ200 < 0) meanAnomalyAtJ200 += 2_pi;

  PlanetID parentId(parentName);

  Orbit orbit(parentId, semiMajorAxis, eccentricity, glm::radians(inclination),
              glm::radians(longitudeOfAscendingNode),
              glm::radians(argumentOfPeriapsis), meanAnomalyAtJ200);

  auto planet =
      CelestialPtr(new Planet(mass, radius, surfacePressure, orbit, name));
  planet->setOrbit(orbit);
  auto mesh = meshFabric.createMesh(tree.get_child("mesh"));
  planet->setMesh(mesh);
  planet->setPosition(glm::vec3(random() * 10.f, 0.f, 0.f));
  solarSystem->addPlanet(std::move(planet));
}
}
}
