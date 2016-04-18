#pragma once
#include "CelestialObject.hpp"
#include "Orbit.hpp"

namespace oa {
namespace game {
class Planet : public CelestialObject {
 public:
  Planet(double, double, double, Orbit, std::string);
  ~Planet();
  glm::vec3 getPoint();
  glm::vec3 getVelocity();

 private:
  Orbit orbit;
  double mass;
  double radius;
  double surfacePressure;
};
}
}
