#pragma once
#include <map>
#include <string>
#include "Camera.hpp"
#include "Geometry.hpp"
#include "Object.hpp"
#include "ShaderProgam.hpp"
#include "Uniform.hpp"
#include "UniformHolder.hpp"

namespace oa {
namespace render {
class Mesh : public render::Object, public render::UniformHolder {
  ShaderProgram *program;
  geometry::Geometry *geometry;
  glm::mat4 modelViewProjection;

 public:
  geometry::Geometry *getGeometry();
  ShaderProgram *getShader();
  Mesh(ShaderProgram *, geometry::Geometry *);
  virtual uint32_t getProgramId();
  virtual void render();

  virtual void prerender(const UniformHolder *uniformSource);
  virtual void setupUniforms(const Camera *);
  virtual ~Mesh(){};
};
}
}
