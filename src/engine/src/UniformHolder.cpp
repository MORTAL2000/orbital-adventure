#include <iostream>
#include "UniformHolder.hpp"
namespace oa {
namespace render {

void UniformOwner::setUniformValue(std::string name, Uniform* u) {
  uniforms[name] = std::unique_ptr<Uniform>(u);
}
bool UniformOwner::setupUniform(std::string& name, uint32_t location) const {
  if (!uniforms.count(name)) return false;
  uniforms.at(name)->setup(location);
  return true;
}

void UniformPtrHolder::setUniformValue(std::string name, Uniform* u) {
  uniforms[name] = u;
}

bool UniformPtrHolder::setupUniform(std::string& name,
                                    uint32_t location) const {
  if (!uniforms.count(name)) return false;
  uniforms.at(name)->setup(location);
  return true;
}

const Uniform* UniformOwner::operator[](std::string& s) {
  return uniforms[s].get();
}
std::vector<std::string> UniformPtrHolder::getUniformNames() {
  std::vector<std::string> r;
  for (auto& p : uniforms) r.push_back(p.first);
  return r;
}

Uniform* UniformPtrHolder::operator[](std::string& s) { return uniforms[s]; }
}
}
