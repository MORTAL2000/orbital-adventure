#pragma once
#include <map>
#include <string>
#include <boost/signals2.hpp>
#include "Camera.hpp"
#include "Geometry.hpp"
#include "Object.hpp"
#include "ShaderProgam.hpp"
#include "Uniform.hpp"
#include "UniformHolder.hpp"
#include "UniformInstaller.hpp"

namespace oa {
namespace render {
class Mesh : public render::Object, public render::UniformHolder {
  ShaderProgram *program;
  geometry::Geometry *geometry;
  glm::mat4 modelViewProjection;
  std::vector<std::unique_ptr<UniformInstaller>> uniformInstallers;

  std::function<std::unique_ptr<Camera>(const Camera *)> cameraModifier;

 public:
  geometry::Geometry *getGeometry();
  ShaderProgram *getShader();
  Mesh(ShaderProgram *, geometry::Geometry *);
  virtual uint32_t getProgramId();
  virtual void prerender(const UniformHolder *uniformSource);
  virtual void addUniformInstaller(UniformInstaller *);
  virtual void setupUniforms(const Camera *, double t);
  virtual void updateUniformInstallers(const Camera *, double t);
  virtual ~Mesh(){};
};
}
}
