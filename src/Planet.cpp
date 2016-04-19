#include <iostream>
#include "Planet.hpp"

namespace oa {
namespace game {
bool Planet::hasOrbit() { return true; }
Planet::Planet(double m, double rad, double atm, Orbit o, std::string n)
    : CelestialObject(n, m), orbit(o), radius(rad), surfacePressure(atm) {
  std::cout << "planet constructed\n";
}
Planet::~Planet() { std::cout << "planet deconstructed\n"; }

glm::vec3 Planet::getPoint() { return glm::vec3(1, 1, 1); }

glm::vec3 Planet::getVelocity() { return glm::vec3(1, 1, 1); }
}
}
