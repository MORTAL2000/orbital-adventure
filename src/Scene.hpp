#pragma once
#include <map>
#include <set>
#include <vector>
#include "Geometry.hpp"
#include "Mesh.hpp"
#include "ShaderProgam.hpp"
namespace oa {
namespace render {
class Scene {
  std::map<const ShaderProgram *, std::set<geometry::Geometry *>>
      materialGeometryMap;
  std::map<const geometry::Geometry *, std::set<Mesh *>> geometryMeshMap;
  std::set<ShaderProgram *> shaders;

 public:
  void addMesh(Mesh *);
  const std::set<ShaderProgram *> &getAllShaders() const;
  const std::set<geometry::Geometry *> &getGeometries(
      const ShaderProgram *) const;
  const std::set<Mesh *> &getMeshes(const geometry::Geometry *) const;
};
}
}
