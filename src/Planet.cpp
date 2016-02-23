#include "Planet.hpp"
#include "PlanetMesh.hpp"

namespace oa {
namespace game {
Planet::Planet(double m, double rad, double atm, Orbit o, std::string n)
    : CelestialObject(n),
      orbit(o),
      mass(m),
      radius(rad),
      surfacePressure(atm) {}

glm::vec3 Planet::getPoint() { return glm::vec3(1, 1, 1); }

glm::vec3 Planet::getVelocity() { return glm::vec3(1, 1, 1); }
}
}
