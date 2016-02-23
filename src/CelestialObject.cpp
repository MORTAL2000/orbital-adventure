#include "CelestialObject.hpp"

namespace oa {
namespace game {
void CelestialObject::setMesh(std::shared_ptr<render::Mesh> m) { mesh = m; }
CelestialObject::CelestialObject(std::string n) : name(n){};
}
}
