#pragma once
#include <memory>
#include "Geometry.hpp"
#include "ShaderProgam.hpp"
#include "UniformHolder.hpp"
namespace oa {
namespace render {
class TextureCreator : public UniformHolder {
  std::string target;
  ShaderProgram* shaderProgram;
  geometry::Geometry* geometry;

 public:
  virtual ~TextureCreator() {}
  virtual std::string getTarget() = 0;
  virtual bool needsDepthTest() = 0;
  virtual size_t supposedWidth() = 0;
  virtual size_t supposedHeight() = 0;
  TextureCreator(ShaderProgram*, std::string target);
  virtual void render() = 0;
};
}
}
