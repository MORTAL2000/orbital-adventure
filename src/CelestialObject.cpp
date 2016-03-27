#include "CelestialObject.hpp"
#include <iostream>

namespace oa {
namespace game {
void CelestialObject::setMesh(render::Mesh* m) {
  std::cout << "set mesh\n";
  mesh = m;
}
CelestialObject::CelestialObject(std::string n) : name(n) {
  std::cout << "CO" << name << "\n";
};
}
}
