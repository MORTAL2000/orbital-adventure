#pragma once
#include "PlanetID.hpp"
namespace oa {
namespace game {

class Orbit {
 public:
  Orbit() = default;
  Orbit(PlanetID, double sma, double ecc, double inc, double lan, double aop,
        double man);
  PlanetID body;
  double semiMajorAxis;
  double eccentricity;
  double inclination;
  double longitudeOfAscendingNode;
  double argumentOfPeriapsis;
  double meanAnomaly;
};
}
}
