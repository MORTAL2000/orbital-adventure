#include "Orbit.hpp"
namespace oa {
namespace game {
/*
Orbit::Orbit()
  : body(""),
    semiMajorAxis(0.0),
    eccentricity(0.0),
    inclination(0.0),
    longitudeOfAscendingNode(0.0),
    argumentOfPeriapsis(0.0),
    meanAnomaly(0.0) {}
    */
Orbit::Orbit(PlanetID id, double sma, double ecc, double inc, double lan,
             double aop, double man)
    : body(id),
      semiMajorAxis(sma),
      eccentricity(ecc),
      inclination(inc),
      longitudeOfAscendingNode(lan),
      argumentOfPeriapsis(aop),
      meanAnomaly(man) {}
}
}
