#pragma once
#include "CelestialObject.hpp"
namespace oa {
namespace game {
class Star : public CelestialObject {
 public:
  Star(double m, double r, std::string n);
  glm::vec3 getPoint();
  glm::vec3 getVelocity();

 private:
  bool hasOrbit();
};
}
}
