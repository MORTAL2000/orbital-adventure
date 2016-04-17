#include "PlanetInFocusCommandProvider.hpp"
#include "ChangePlanetCommand.hpp"
#include <iostream>
namespace oa {
namespace game {
PlanetInFocusCommandProvider::PlanetInFocusCommandProvider(
    CommandAcceptor *acceptor, SolarSystem *ss, CelestialCameraManager *camMgr)
    : CommandProvider(acceptor),
      solarSystem(ss),
      cameraMgr(camMgr),
      planetMap(solarSystem->getPlanetMap()),
      currentIterator(planetMap.cbegin()) {
  createCommand();
}
void PlanetInFocusCommandProvider::createCommand() {
  addCommand(new ChangePlanetCommand(cameraMgr, currentIterator->second.get()));
}
void PlanetInFocusCommandProvider::onKeyUp(int keyCode, int mods) {
  std::cout << keyCode << " next planet\n";
  if (keyCode == 44)  // <
    if (currentIterator != planetMap.cbegin()) {
      --currentIterator;
      createCommand();
    }
  if (keyCode == 46)
    if (currentIterator != --planetMap.cend()) {
      ++currentIterator;
      createCommand();
    }
}
}
}
