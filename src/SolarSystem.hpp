#pragma once
#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <memory>
#include <string>
#include "CelestialObject.hpp"
#include "PlanetID.hpp"
#include "engine/Mesh.hpp"
#include "engine/MeshFabric.hpp"
#include "engine/Scene.hpp"

namespace oa {
namespace game {
typedef std::unique_ptr<CelestialObject> CelestialPtr;
class SolarSystem {
  const static double G;

 public:
  typedef std::map<PlanetID, CelestialPtr> CelestialMap;
  typedef const std::map<PlanetID, CelestialPtr> &CelestialMapRef;

 private:
  CelestialMap celestialsMap;
  render::Scene scene;

  double trueAnomaly(double eccentricity, double E, double precision);
  double eccentricityAnomaly(double eccentricity, double anomaly);
  glm::vec3 planetPlaneCoordinates(Orbit &orbit, double moment, double M,
                                   double m);
  double getMoment(int year, int month, int day,
                   uint32_t millisecondsTillDayStart);

 public:
  SolarSystem();
  void addPlanet(CelestialPtr);
  void updatePlanets(long);
  const render::Scene *getScene();
  CelestialMapRef getPlanetMap() const;
};
}
}
