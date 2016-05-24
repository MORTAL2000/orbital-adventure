#include "ChangePlanetCommand.hpp"
namespace oa {
namespace game {
ChangePlanetCommand::ChangePlanetCommand(CelestialCameraManager *mgr,
                                         const CelestialObject *planet)
    : cameraMgr(mgr), planet(planet) {}

void ChangePlanetCommand::execute() { cameraMgr->setCurrentCelestial(planet); }
}
}
