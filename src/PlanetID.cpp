#include "PlanetID.hpp"
namespace oa {
namespace game {
PlanetID::PlanetID(std::string n) : planetName(n) {}
bool PlanetID::operator<(const PlanetID& o) const {
  return planetName < o.planetName;
}
bool PlanetID::operator<(const PlanetID& o) {
  return planetName < o.planetName;
}
std::string PlanetID::id() const { return planetName; }
}
}
