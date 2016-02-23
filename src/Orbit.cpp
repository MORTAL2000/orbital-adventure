#include "Orbit.hpp"
namespace oa {
namespace game {
Orbit::Orbit(PlanetID id, double sma, double ecc, double inc, double lan, double aop, double man):
  body(id), semiMajorAxis(sma),eccentricity(ecc),
  inclination(inc), longitudeOfAscendingNode(lan),
  argumentOfPeriapsis(aop), meanAnomaly(man) { }
}
}

