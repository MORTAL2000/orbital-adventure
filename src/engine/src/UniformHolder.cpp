#include <iostream>
#include "UniformHolder.hpp"
namespace oa {
namespace render {

void UniformOwner::setUniformValue(std::string name, Uniform* u) {
  uniforms[name] = std::unique_ptr<Uniform>(u);
}
bool UniformOwner::setupUniform(const std::string& name,
                                uint32_t location) const {
  if (!uniforms.count(name)) return false;
  uniforms.at(name)->setup(location);
  return true;
}

Uniform* UniformOwner::copy(std::string& name) {
  if (!uniforms.count(name)) return nullptr;
  return uniforms[name]->clone();
}

void UniformPtrHolder::setUniformValue(std::string name, Uniform* u) {
  uniforms[name] = u;
}

bool UniformPtrHolder::setupUniform(const std::string& name,
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
Uniform* UniformPtrHolder::copy(std::string& name) {
  if (!uniforms.count(name)) return nullptr;
  return uniforms[name]->clone();
}
}
}
