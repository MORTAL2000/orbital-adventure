#include <iostream>
#include "UniformHolder.hpp"
namespace oa {
namespace render {
void UniformHolder::moveUniforms(std::vector<std::string>& names,
                                 UniformHolder* from) {
  for (auto& n : names) {
    std::cout << "moving uniforms: " << n << "\n";
    for (auto& p : from->uniforms) {
      std::cout << "FROM CONTAIN : " << p.first << "\n";
    }
    if (from->uniforms.count(n)) {
      this->uniforms[n] = std::move(from->uniforms[n]);
      from->uniforms.erase(n);
    } else {
      std::cerr << "Cannot move uniform  " << n << "\n";
    }
  }
}
void UniformHolder::moveUniforms(std::vector<std::string>&& names,
                                 UniformHolder* from) {
  for (auto& n : names) {
    std::cout << "moving uniforms: " << n << "\n";
    if (from->uniforms.count(n)) {
      this->uniforms[n] = std::move(from->uniforms[n]);
      from->uniforms.erase(n);
    } else {
      std::cerr << "Cannot move uniform  " << n << "\n";
    }
  }
}

void UniformHolder::moveUniforms(UniformHolder* from) {
  for (auto& p : from->uniforms) {
    std::cout << " <<<<< " << p.first << "\n";
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
