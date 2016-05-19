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
  glm::vec3 betaR;
  glm::vec3 betaMSca;
  float HR;
  float HM;
  render::Mesh* mesh;

 public:
  const Orbit& getOrbit();
  double getMass();
  void setPosition(glm::dvec3);
  glm::dvec3 getPosition();
  glm::dvec3 getPosition() const;

  void setMesh(render::Mesh*);
  virtual bool hasOrbit() = 0;
  virtual bool hasAtmosphere() = 0;
  void setOrbit(const Orbit& orbit);
  CelestialObject(std::string n, double mass, double size);
  double getSize();
  double getSize() const;
  std::string getName();
  void setHM(float);
  float getHM() const;
  void setHR(float);
  float getHR() const;
  void setBetaMSca(glm::vec3);
  glm::vec3 getBetaMSca() const;
  void setBetaR(glm::vec3);
  glm::vec3 getBetaR() const;
  std::string getName() const;
  render::Mesh* getMesh();
  const render::Mesh* getMesh() const;
  virtual ~CelestialObject(){};
  void updateMesh(const CelestialObject*);
};
}
}
