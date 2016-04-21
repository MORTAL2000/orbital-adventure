#pragma once
#include <glm/vec3.hpp>
#include <string>
#include "Orbit.hpp"
#include "engine/Mesh.hpp"
namespace oa {
namespace game {
class CelestialObject {
  Orbit orbit;
  double mass;
  double size;
  std::string name;
  glm::dvec3 position;
  render::Mesh* mesh;

 public:
  const Orbit& getOrbit();
  double getMass();
  void setPosition(glm::dvec3);
  glm::dvec3 getPosition();
  glm::dvec3 getPosition() const;

  void setMesh(render::Mesh*);
  virtual bool hasOrbit() = 0;
  void setOrbit(const Orbit& orbit);
  CelestialObject(std::string n, double mass, double size);
  double getSize();
  double getSize() const;
  std::string getName();
  std::string getName() const;

  render::Mesh* getMesh();
  virtual ~CelestialObject(){};
  void updateMesh(const CelestialObject*);
};
}
}
