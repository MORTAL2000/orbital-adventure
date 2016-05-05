#include <iostream>
#include "LanguageUtils.hpp"
#include "Scene.hpp"

namespace oa {
namespace render {
using namespace utils;
void Scene::addMesh(Mesh* meshptr) {
  auto geometry = meshptr->getGeometry();
  auto shader = meshptr->getShader();
  meshes.push_back(meshptr);
  shaders.emplace(shader);
  if (materialGeometryMap.count(shader) == 0)
    materialGeometryMap[shader] = std::set<geometry::Geometry*>();
  materialGeometryMap[shader].emplace(geometry);
  if (geometryMeshMap.count(geometry) == 0)
    geometryMeshMap[geometry] = std::set<Mesh*>();
  geometryMeshMap[geometry].emplace(meshptr);
}
const std::set<ShaderProgram*>& Scene::getAllShaders() const { return shaders; }
const std::set<geometry::Geometry*>& Scene::getGeometries(
    const ShaderProgram* sp) const {
  return materialGeometryMap.at(sp);
}
const std::set<Mesh*>& Scene::getMeshes(const geometry::Geometry* g) const {
  return geometryMeshMap.at(g);
}
const std::vector<Mesh*> Scene::getSortedMeshes(glm::vec3 position) const {
  std::vector<Mesh*> sortedMeshes;
  for (auto& m : meshes) {
    sortedMeshes.push_back(m);
  }

  std::sort(sortedMeshes.begin(), sortedMeshes.end(),
            [&position](Mesh* a, Mesh* b) {
              return glm::length(a->getPosition() - position) >
                     glm::length(b->getPosition() - position);

            });

  return sortedMeshes;
}
}
}
