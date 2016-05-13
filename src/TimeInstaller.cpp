#include "TimeInstaller.hpp"

namespace oa {
namespace game {
using namespace render;
using namespace std::chrono;
void TimeInstaller::install(UniformHolder *h, const Camera *, double) {
  auto delta = system_clock::now() - started;
  float d = duration_cast<duration<float, std::ratio<1>>>(delta).count();
  h->setUniformValue("time", new render::FloatOwnerUniform(d));
}
TimeInstaller::TimeInstaller() { started = system_clock::now(); }
}
}
