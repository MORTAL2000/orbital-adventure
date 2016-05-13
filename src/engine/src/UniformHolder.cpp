#include <iostream>
#include "UniformHolder.hpp"
namespace oa {
namespace render {
void UniformHolder::moveUniforms(std::vector<std::string>& names,
                                 UniformHolder* from) {
  for (auto& n : names) {
    if (from->uniforms.count(n)) {
      this->uniforms[n] = std::move(from->uniforms[n]);
      from->uniforms.erase(n);
    }
  }
}
void UniformHolder::moveUniforms(std::vector<std::string>&& names,
                                 UniformHolder* from) {
  for (auto& n : names) {
    if (from->uniforms.count(n)) {
      this->uniforms[n] = std::move(from->uniforms[n]);
      from->uniforms.erase(n);
    }
  }
}

void UniformHolder::moveUniforms(UniformHolder* from) {
  for (auto& p : from->uniforms) {
    this->uniforms[p.first] = std::move(p.second);
  }
  from->uniforms.clear();
}
void UniformHolder::setUniformValue(std::string name, Uniform* u) {
  uniforms[name] = std::unique_ptr<Uniform>(u);
}
bool UniformHolder::setupUniform(std::string& name, uint32_t location) const {
  if (!uniforms.count(name)) return false;
  uniforms.at(name)->setup(location);
  return true;
}
}
}
