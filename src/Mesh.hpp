#pragma once
#include <map>
#include <string>
#include "Object.hpp"
#include "ShaderProgam.hpp"
#include "Geometry.hpp"
#include "Uniform.hpp"

namespace oa {
namespace render {
class Mesh : public render::Object {
  ShaderProgram *program;
  geometry::Geometry *geometry;
  std::map<std::string, std::unique_ptr<Uniform>> uniforms;
  glm::mat4 modelViewProjection;

 public:
  geometry::Geometry *getGeometry();
  ShaderProgram *getShader();
  Mesh(ShaderProgram *, geometry::Geometry *);
  virtual void setUniformValue(std::string, Uniform *);
  virtual uint32_t getProgramId();
  virtual void render();

  virtual void setupUniforms(glm::mat4 projection, glm::mat4 view);
  virtual ~Mesh(){};
};
}
}
