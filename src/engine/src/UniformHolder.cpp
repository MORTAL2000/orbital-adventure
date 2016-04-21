#include <iostream>
#include "UniformHolder.hpp"
namespace oa {
namespace render {
void UniformHolder::setUniformValue(std::string name, Uniform* u) {
  uniforms[name] = std::unique_ptr<Uniform>(u);
}
void UniformHolder::setupUniform(std::string& name, uint32_t location) {
  if (!uniforms.count(name)) {
    std::cerr << "No such uniform : " << name << "\n";
  }
  uniforms[name]->setup(location);
}
}
}
