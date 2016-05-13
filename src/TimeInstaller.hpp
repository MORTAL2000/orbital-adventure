#pragma once
#include <chrono>
#include "engine/UniformInstaller.hpp"

namespace oa {
namespace game {
class TimeInstaller : public render::UniformInstaller {
  std::chrono::system_clock::time_point started;
  float time;
  void install(render::UniformHolder *, const render::Camera *, double);

 public:
  TimeInstaller();
};
}
}
