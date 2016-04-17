#pragma once
#include <glm/vec3.hpp>
#include <string>
#include "engine/Mesh.hpp"
namespace oa {
namespace game {
class CelestialObject {
  std::string name;
  virtual glm::vec3 getPoint() = 0;
  virtual glm::vec3 getVelocity() = 0;
  render::Mesh* mesh;

 public:
  virtual void setMesh(render::Mesh*);
  CelestialObject(std::string n);
  virtual ~CelestialObject(){};
};
}
}
