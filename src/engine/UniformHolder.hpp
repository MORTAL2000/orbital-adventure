
#pragma once
#include <map>
#include <memory>
#include <string>
#include "Uniform.hpp"
namespace oa {
namespace render {
class UniformHolder {
  std::map<std::string, std::unique_ptr<Uniform>> uniforms;

 public:
  ~UniformHolder(){};
  void setUniformValue(std::string, Uniform *);
  bool setupUniform(std::string &, uint32_t location) const;
};
}
}
