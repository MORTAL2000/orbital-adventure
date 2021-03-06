
#pragma once
#include <map>
#include <memory>
#include <string>
#include "Uniform.hpp"
namespace oa {
namespace render {
class UniformHolder {
 public:
  virtual ~UniformHolder(){};
  virtual void setUniformValue(std::string, Uniform *) = 0;
  virtual bool setupUniform(const std::string &, uint32_t location) const = 0;
  virtual const Uniform *operator[](std::string &) = 0;
  virtual Uniform *copy(std::string &) const = 0;
};

class UniformOwner : public UniformHolder {
  std::map<std::string, std::unique_ptr<Uniform>> uniforms;

 public:
  virtual void setUniformValue(std::string, Uniform *);
  virtual bool setupUniform(const std::string &, uint32_t location) const;
  virtual const Uniform *operator[](std::string &);
  virtual Uniform *copy(std::string &) const;
};
class UniformPtrHolder : public UniformHolder {
  std::map<std::string, Uniform *> uniforms;
  virtual void setUniformValue(std::string, Uniform *);
  virtual bool setupUniform(const std::string &, uint32_t location) const;
  virtual Uniform *copy(std::string &) const;

 public:
  Uniform *operator[](std::string &);
  std::vector<std::string> getUniformNames();
};
}
}
