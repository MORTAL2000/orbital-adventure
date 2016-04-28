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

namespace oa {
namespace render {
class Mesh : public render::Object, public render::UniformHolder {
  ShaderProgram *program;
  geometry::Geometry *geometry;
  glm::mat4 modelViewProjection;
  std::function<std::unique_ptr<Camera>(const Camera *)> cameraModifier;
  typedef boost::signals2::signal<void(UniformHolder *, double)> SignalType;
  SignalType uniformUpdaters;

 public:
  geometry::Geometry *getGeometry();
  ShaderProgram *getShader();
  Mesh(ShaderProgram *, geometry::Geometry *);
  virtual uint32_t getProgramId();
  virtual void prerender(const UniformHolder *uniformSource);
  virtual void addUniformUpdater(SignalType::slot_function_type fn);
  virtual void setupUniforms(const Camera *);
  virtual void updateUniforms(double t);
  virtual ~Mesh(){};
};
}
}
