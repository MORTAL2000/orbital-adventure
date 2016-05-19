#include <iostream>
#include "CelestialObject.hpp"

namespace oa {
namespace game {
void CelestialObject::setHM(float v) { HM = v; }
float CelestialObject::getHM() const { return HM; }
void CelestialObject::setHR(float v) { HR = v; }
float CelestialObject::getHR() const { return HR; }
void CelestialObject::setBetaMSca(glm::vec3 v) { betaMSca = v; }
glm::vec3 CelestialObject::getBetaMSca() const { return betaMSca; }
void CelestialObject::setBetaR(glm::vec3 v) { betaR = v; }
glm::vec3 CelestialObject::getBetaR() const { return betaR; }

double CelestialObject::getSize() { return size; }
double CelestialObject::getSize() const { return size; }
void CelestialObject::updateMesh(const CelestialObject* celestial) {
  glm::dvec3 myPosition = position - celestial->getPosition();
  // std::cout << this->getName() << "\n";  //  << " Set " << myPosition.x << "
  // " <<
  // myPosition.y
  //<< " " << myPosition.z << "\n";
  mesh->setPosition(myPosition);
  // std::cout << "set size " << size << "\n";
  mesh->setScale(glm::vec3(size, size, size));
}

std::string CelestialObject::getName() { return name; }
std::string CelestialObject::getName() const { return name; }
render::Mesh* CelestialObject::getMesh() { return mesh; }
const render::Mesh* CelestialObject::getMesh() const { return mesh; }

const Orbit& CelestialObject::getOrbit() { return orbit; }
double CelestialObject::getMass() { return mass; }
void CelestialObject::setOrbit(const Orbit& orbit) { this->orbit = orbit; }
glm::dvec3 CelestialObject::getPosition() { return position; }
glm::dvec3 CelestialObject::getPosition() const { return position; }
void CelestialObject::setPosition(glm::dvec3 p) { this->position = p; }

void CelestialObject::setMesh(render::Mesh* m) { mesh = m; }

CelestialObject::CelestialObject(std::string n, double mass, double size)
    : name(n), mass(mass), size(size), mesh(nullptr){};
}
}
