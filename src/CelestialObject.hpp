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
  void setPosition(glm::vec3);
  glm::vec3 getPosition();
  glm::vec3 getPosition() const;
  virtual void setMesh(render::Mesh*);
  void setOrbit(const Orbit& orbit);
  CelestialObject(std::string n);
  std::string getName();
  render::Mesh* getMesh();
  virtual ~CelestialObject(){};
};
}
}
