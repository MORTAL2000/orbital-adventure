#include <iostream>
#include "OAUniformInstallerFabric.hpp"
#include "Planet.hpp"
#include "SolarSystemCreator.hpp"
#include "Star.hpp"
#include "SunDirectionUniformInstaller.hpp"
#include "engine/LanguageUtils.hpp"

namespace oa {
namespace game {
using namespace utils;
using boost::property_tree::ptree;

SolarSystemCreator::SolarSystemCreator() : solarSystem(new SolarSystem) {}
std::unique_ptr<SolarSystem> SolarSystemCreator::getSolarSystem() {
  return std::move(solarSystem);
}
std::vector<render::TextureCreator *> SolarSystemCreator::getTextureCreators() {
  return textureCreators;
}
void SolarSystemCreator::createTextureCreator(ptree &tCreator) {
  render::TextureCreator *tc = textureCreatorFabric.make(tCreator);
  if (tc)
    textureCreators.push_back(tc);
  else
    std::cerr << "NO CREATOR\n";
}
void SolarSystemCreator::setupUniformUpdaters(
    const CelestialCameraManager *cameraMgr) {}
void SolarSystemCreator::createSolarSystem(std::string filepath) {
  meshFabric.setRootDir(filepath);
  textureCreatorFabric.setRootDir(filepath);
  auto uf = new render::UniformFabric;
  uf->setRootDir(filepath);
  meshFabric.setUniformFabric(uf);
  auto uif = new OAUniformInstallerFabric;
  uif->setRootDir(filepath);
  meshFabric.setUniformInstallerFabric(uif);

  uf = new render::UniformFabric;
  uf->setRootDir(filepath);
  textureCreatorFabric.setUniformFabric(uf);
  uif = new OAUniformInstallerFabric;
  uif->setRootDir(filepath);
  textureCreatorFabric.setUniformInstallerFabric(uif);
  textureCreatorFabric.setDefaultVertexShaderPath("shaders/screenVShader.glsl");

  ptree planetsTree;
  read_json(filepath, planetsTree);
  boost::property_tree::ptree sb = planetsTree.get_child("skybox");
  createSkyBox(sb);
  for (auto &creator : planetsTree.get_child("texture-creators"))
    createTextureCreator(creator.second);
  for (auto &v : planetsTree.get_child("planets")) parsePlanet(v);
}

void SolarSystemCreator::createSkyBox(boost::property_tree::ptree &tree) {
  std::vector<std::string> textures;
  textures.push_back(tree.get<std::string>("px"));
  textures.push_back(tree.get<std::string>("nx"));
  textures.push_back(tree.get<std::string>("py"));
  textures.push_back(tree.get<std::string>("ny"));
  textures.push_back(tree.get<std::string>("pz"));
  textures.push_back(tree.get<std::string>("nz"));
  std::string vs = tree.get("vertexShader", "no shader");
  std::string fs = tree.get("fragmentShader", "no shader");

  render::Mesh *mesh = meshFabric.createSkyboxMesh(textures, vs, fs);
  solarSystem->setSkybox(mesh);
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
    sunMesh = mesh;
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
  mesh->addUniformInstaller(new SunDirectionUniformInstaller(sunMesh, mesh));
  planet->setMesh(mesh);
  planet->setPosition(glm::vec3(random() * 10.f, 0.f, 0.f));
  solarSystem->addPlanet(std::move(planet));
}
}
}
