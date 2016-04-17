#pragma once
#include "engine/Camera.hpp"
#include "CameraControlCommandProvider.hpp"
#include "PlanetInFocusCommandProvider.hpp"
#include "CommandAcceptor.hpp"
#include "engine/GLFWWrapper.hpp"
#include "GameEventsCommandProvider.hpp"
#include "engine/Renderer.hpp"
#include "SolarSystem.hpp"
#include "CelestialCameraManager.hpp"

namespace oa {
namespace game {
class Game : public CommandAcceptor {
 public:
  Game();
  void init();
  void mainLoop();
  void stopGame();

 private:
  std::vector<std::unique_ptr<CommandProvider>> providers;
  void initGLFW();
  void initSolarSystem();
  void initPlayer();
  bool isPlaying;
  void initCommandsInf();
  gl::GLFWWrapper *glfw;
  void deinit();
  SolarSystem solarSystem;
  render::Renderer renderer;
  // render::Camera *camera;
  CelestialCameraManager cameraManager;
};
}
}
