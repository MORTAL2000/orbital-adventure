#include "Planet.hpp"
#include <iostream>

namespace oa {
namespace game {
Planet::Planet(double m, double rad, double atm, Orbit o, std::string n)
    : CelestialObject(n), orbit(o), mass(m), radius(rad), surfacePressure(atm) {
  std::cout << "planet constructed\n";
}
Planet::~Planet() { std::cout << "planet deconstructed\n"; }

glm::vec3 Planet::getPoint() { return glm::vec3(1, 1, 1); }

glm::vec3 Planet::getVelocity() { return glm::vec3(1, 1, 1); }
}
}
