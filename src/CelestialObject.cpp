#include "CelestialObject.hpp"
#include <iostream>

namespace oa {
namespace game {
void CelestialObject::setOrbit(const Orbit& orbit) { this->orbit = orbit; }
glm::vec3 CelestialObject::getPosition() { return position; }
glm::vec3 CelestialObject::getPosition() const { return position; }
void CelestialObject::setPosition(glm::vec3 p) {
  this->position = p;
  if (mesh) mesh->setPosition(position);
}

void CelestialObject::setMesh(render::Mesh* m) { mesh = m; }
CelestialObject::CelestialObject(std::string n) : name(n), mesh(nullptr){};
}
}
