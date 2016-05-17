#pragma once
#include "Geometry.hpp"
#include "ShaderProgam.hpp"
#include "UniformHolder.hpp"
#include "UniformInstaller.hpp"
namespace oa {
namespace render {
class Filter {
  std::unique_ptr<UniformHolder> uniforms;
  std::vector<std::unique_ptr<UniformInstaller>> uniformInstallers;
  std::vector<std::string> targets;
  ShaderProgram *shader;
  std::vector<std::function<void()>> glSettings;
  geometry::Geometry *geometry;

 public:
  std::vector<std::string> &getTargets();
  void addUniformInstaller(UniformInstaller *);
  GLuint getProgramId();
  geometry::Geometry *getGeometry();
  void updateUniforms();
  void setupRenderingMode();
  void addGLSettings(std::function<void()>);
  Filter(std::string fragmentPath);
};
}
}
