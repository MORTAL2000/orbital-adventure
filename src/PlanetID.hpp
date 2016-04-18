#pragma once
#include <string>
namespace oa {
namespace game {
class PlanetID {
 public:
  PlanetID() = default;
  PlanetID(std::string);
  bool operator<(const PlanetID &o);
  bool operator<(const PlanetID &o) const;
  std::string id() const;

 private:
  std::string planetName;
  std::string planetID;
};
}
}
