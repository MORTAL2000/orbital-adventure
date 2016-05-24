#pragma once
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <chrono>
#include <map>
#include <memory>
#include <string>
#include "../engine/Mesh.hpp"
#include "../engine/Scene.hpp"
#include "CelestialObject.hpp"
#include "PlanetID.hpp"

namespace oa {
namespace game {
class CelestialCameraManager;

typedef std::unique_ptr<CelestialObject> CelestialPtr;
class SolarSystem {
  const static double G;

 public:
  typedef std::map<PlanetID, CelestialPtr> CelestialMap;
  typedef const std::map<PlanetID, CelestialPtr> &CelestialMapRef;
  typedef std::chrono::duration<double, std::ratio<1>> FloatDuration;

 private:
  std::chrono::system_clock::time_point epoch2000;
  CelestialMap celestialsMap;
  render::Scene scene;
  render::Scene skyboxScene;
  const CelestialObject *objectOfIntrest;

  double trueAnomaly(double eccentricity, double E, double precision);
  double eccentricityAnomaly(double eccentricity, double anomaly);
  glm::dvec3 planetPlaneCoordinates(const Orbit &orbit, double moment, double M,
                                    double m);
  double getMoment(std::chrono::system_clock::time_point &);

 public:
  SolarSystem();
  void addPlanet(CelestialPtr);
  void updatePlanets(std::chrono::system_clock::time_point &);
  void setCurrentCelestial(const CelestialObject *);
  const CelestialObject *getObjectOfInterest();
  const CelestialObject *getObjectOfInterest() const;
  const CelestialObject *getSun() const;
  render::Scene *getScene();
  const render::Scene *getSkyboxScene();
  void setSkybox(render::Mesh *m);
  CelestialMapRef getPlanetMap() const;
};
}
}
