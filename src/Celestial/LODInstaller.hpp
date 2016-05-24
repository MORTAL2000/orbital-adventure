#pragma once
#include "Camera.hpp"
#include "LODTextureManager.hpp"
#include "Mesh.hpp"
#include "UniformHolder.hpp"
#include "UniformInstaller.hpp"

namespace oa {
namespace render {
class LODInstaller : public render::UniformInstaller {
  const render::Mesh *mesh;
  void initLODTextures();
  void setupLODTextures();
  glm::vec2 currentPosition;
  LODTextureManager lodManager;
  void install(render::UniformHolder *, const Camera *, double);

 public:
  LODInstaller(const render::Mesh *, LODTextureManager &&);
};
}
}
