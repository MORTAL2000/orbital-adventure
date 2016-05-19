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
  Uniform* u = uniforms.at(name).get();
  u->setup(location);
  return true;
}

Uniform* UniformOwner::copy(std::string& name) const {
  if (!uniforms.count(name)) {
    std::cerr << "cannot copy uniform " << name << ", it's not exists \n";
    return nullptr;
  }
  return uniforms.at(name)->clone();
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
Uniform* UniformPtrHolder::copy(std::string& name) const {
  if (!uniforms.count(name)) return nullptr;
  return uniforms.at(name)->clone();
}
}
}
