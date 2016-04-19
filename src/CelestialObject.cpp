#include <iostream>
#include "CelestialObject.hpp"

namespace oa {
namespace game {
std::string CelestialObject::getName() { return name; }
render::Mesh* CelestialObject::getMesh() { return mesh; }

const Orbit& CelestialObject::getOrbit() { return orbit; }
double CelestialObject::getMass() { return mass; }
void CelestialObject::setOrbit(const Orbit& orbit) { this->orbit = orbit; }
glm::vec3 CelestialObject::getPosition() { return position; }
glm::vec3 CelestialObject::getPosition() const { return position; }
void CelestialObject::setPosition(glm::vec3 p) {
  this->position = p;
  if (mesh) mesh->setPosition(position);
}

void CelestialObject::setMesh(render::Mesh* m) { mesh = m; }

CelestialObject::CelestialObject(std::string n, double mass)
    : name(n), mass(mass), mesh(nullptr){};
}
}
