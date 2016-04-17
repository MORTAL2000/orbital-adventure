#include "PlanetInFocusCommandProvider.hpp"
namespace oa {
namespace game {
PlanetInFocusCommandProvider::PlanetInFocusCommandProvider(
    CommandAcceptor *acceptor, SolarSystem *ss, CelestialCameraManager *camMgr)
    : CommandProvider(acceptor), solarSystem(ss), cameraMgr(camMgr) {}
}
}
