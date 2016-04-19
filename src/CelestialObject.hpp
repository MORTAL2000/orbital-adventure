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
  std::string name;
  glm::vec3 position;
  virtual glm::vec3 getPoint() = 0;
  virtual glm::vec3 getVelocity() = 0;
  render::Mesh* mesh;

 public:
  const Orbit& getOrbit();
  double getMass();
  void setPosition(glm::vec3);
  glm::vec3 getPosition();
  glm::vec3 getPosition() const;
  virtual void setMesh(render::Mesh*);
  virtual bool hasOrbit() = 0;
  void setOrbit(const Orbit& orbit);
  CelestialObject(std::string n, double mass);
  std::string getName();
  render::Mesh* getMesh();
  virtual ~CelestialObject(){};
};
}
}
