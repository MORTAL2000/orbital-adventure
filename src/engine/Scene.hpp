#pragma once
#include <map>
#include <set>
#include <vector>
#include "Geometry.hpp"
#include "Mesh.hpp"
#include "ShaderProgam.hpp"
#include "UniformHolder.hpp"
namespace oa {
namespace render {
class Scene : public UniformHolder {
  std::vector<Mesh *> meshes;
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
  const std::vector<Mesh *> getSortedMeshes(glm::vec3) const;
};
}
}
