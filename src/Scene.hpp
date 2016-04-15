#pragma once
#include "ShaderProgam.hpp"
#include "Geometry.hpp"
#include "Mesh.hpp"
#include <vector>
#include <map>
#include <set>
namespace oa {
namespace render {
class Scene {
  std::map<const ShaderProgram *, std::set<geometry::Geometry *>>
      materialGeometryMap;
  std::map<const geometry::Geometry *, std::set<Mesh *>> geometryMeshMap;
  std::set<ShaderProgram *> shaders;

 public:
  void addMesh(Mesh *);
  const std::set<ShaderProgram *> &getAllShaders();
  const std::set<geometry::Geometry *> &getGeometries(const ShaderProgram *);
  const std::set<Mesh *> &getMeshes(const geometry::Geometry *);
};
}
}
