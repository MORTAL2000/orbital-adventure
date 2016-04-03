#include "SolarSystem.hpp"
#include "Star.hpp"
#include "Planet.hpp"
#include "PlanetMesh.hpp"
#include "StarMesh.hpp"
#include <boost/filesystem.hpp>

namespace oa {
namespace game {
SolarSystem::SolarSystem() : planetFilePath("../data/planets.json") {
  meshFabric.setRootDir(planetFilePath);
}

void SolarSystem::createPlanets() {
  using boost::property_tree::ptree;
  ptree planetsTree;
  read_json(planetFilePath, planetsTree);
  for (auto &v : planetsTree) parsePlanet(v);
}

inline float random() { return float(std::rand()) / (std::pow(2, 32) / 2); }

void SolarSystem::parsePlanet(boost::property_tree::ptree::value_type &value) {
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
    celestialMeshes.insert(std::make_pair(id, mesh));
    star->setMesh(mesh);
    celestialsMap.insert(std::make_pair(id, std::move(star)));
    return;
  }
  double meanAnomaly = tree.get("meanAnomaly", -10000.0f);
  double meanLongitude = tree.get("meanLongitude", -10000.0f);
  double longitudeOfAscendingNode =
      tree.get<double>("longitudeOfAscendingNode");
  double argumentOfPeriapsis = tree.get<double>("argumentOfPeriapsis");
  double inclination = tree.get<double>("inclination");
  double eccentricity = tree.get<double>("eccentricity");
  double semiMajorAxis = tree.get<double>("semiMajorAxis");
  double surfacePressure = tree.get<double>("surfacePressure");
  if (meanAnomaly < -9000 && meanLongitude > -9000)
    meanAnomaly =
        meanLongitude - longitudeOfAscendingNode + argumentOfPeriapsis;

  Orbit orbit(id, semiMajorAxis, eccentricity, inclination,
              longitudeOfAscendingNode, argumentOfPeriapsis, meanAnomaly);
  auto planet =
      CelestialPtr(new Planet(mass, radius, surfacePressure, orbit, name));
  auto mesh = meshFabric.createMesh(tree.get_child("mesh"));
  celestialMeshes.insert(std::make_pair(id, mesh));
  mesh->setPosition(glm::vec3(random() * 10.f, 0.f, 0.f));
  mesh->setRotation(glm::quat(1.f, 0.f, 0.f, 0.f));
  mesh->setScale(glm::vec3(1.f, 1.f, 1.f));
  planet->setMesh(mesh);
  celestialsMap.insert(std::make_pair(id, std::move(planet)));
}

const std::map<PlanetID, MeshPtr> *const SolarSystem::getCelestialMeshes()
    const {
  return &celestialMeshes;
}
}
}
