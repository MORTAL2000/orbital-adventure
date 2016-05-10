#pragma once
#include <boost/property_tree/ptree.hpp>
#include "Uniform.hpp"

namespace oa {
namespace render {
class UniformFabric {
  std::string rootDir;

 public:
  Uniform *create(boost::property_tree::ptree &);
  void setRootDir(std::string);
};
}
}
