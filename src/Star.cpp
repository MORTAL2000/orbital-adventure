#include "Star.hpp"
namespace oa {
namespace game {
Star::Star(double m, double r, std::string n)
    : CelestialObject(n), mass(m), radius(r) {}

glm::vec3 Star::getVelocity() { return glm::vec3(0); }
glm::vec3 Star::getPoint() { return glm::vec3(0); }
}
}
