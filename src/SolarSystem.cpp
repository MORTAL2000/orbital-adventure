#include "SolarSystem.hpp"
#include "Star.hpp"
#include "Planet.hpp"
#include "PlanetMesh.hpp"
#include "StarMesh.hpp"

namespace oa {
namespace game {
SolarSystem::SolarSystem() : planetFilePath("../data/planets.json") {}

void SolarSystem::createPlanets() {
  using boost::property_tree::ptree;
  ptree planetsTree;
  read_json(planetFilePath, planetsTree);
  for (auto &v : planetsTree) parsePlanet(v);
}

void SolarSystem::parsePlanet(boost::property_tree::ptree::value_type &value) {
  auto tree = value.second;
  std::string name = tree.get<std::string>("name");
  PlanetID id(name);
  bool isStar = tree.get("isStar", false);
  double mass = tree.get<double>("mass");
  double radius = tree.get<double>("radius");
  if (isStar) {
    auto star = CelestialPtr(new Star(mass, radius, name));
    auto mesh = createMesh(tree.get_child("mesh"));
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
  auto mesh = createMesh(tree.get_child("mesh"));
  celestialMeshes.insert(std::make_pair(id, mesh));
  planet->setMesh(mesh);
  celestialsMap.insert(std::make_pair(id, std::move(planet)));
}
inline float random() { return float(std::rand()) / (std::pow(2, 32) / 2); }

MeshPtr SolarSystem::createMesh(boost::property_tree::ptree meshDescription) {
  std::string meshType = meshDescription.get<std::string>("type");
  auto diffuseMap = meshDescription.get_optional<std::string>("diffuse");
  auto normalMap = meshDescription.get_optional<std::string>("normal");
  auto specularMap = meshDescription.get_optional<std::string>("specular");
  if (meshType == "StarMesh") {
    return new render::StarMesh;
  }
  if (meshType == "PlanetMesh") {
    render::PlanetMesh *meshPtr = new render::PlanetMesh;

    if (diffuseMap) meshPtr->setDiffuse(*diffuseMap);
    if (normalMap) meshPtr->setNormal(*normalMap);
    if (specularMap) meshPtr->setSpecular(*specularMap);

    auto rx = random() * 2;
    auto ry = random() * 2;
    auto rz = random() * 2;
    auto pos = glm::vec3(rx, ry, rz);
    meshPtr->setPosition(pos);
    return meshPtr;
  }
}

const std::map<PlanetID, MeshPtr> *const SolarSystem::getCelestialMeshes()
    const {
  return &celestialMeshes;
}
}
}
