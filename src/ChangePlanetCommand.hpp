#include "CelestialObject.hpp"
#include "CelestialCameraManager.hpp"
#include "Command.hpp"
namespace oa {
namespace game {
class ChangePlanetCommand : public Command {
  void execute();
  CelestialCameraManager* cameraMgr;
  const CelestialObject* planet;

 public:
  ChangePlanetCommand(CelestialCameraManager* mgr,
                      const CelestialObject* planet);
};
}
}
