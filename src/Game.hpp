#pragma once
#include <queue>
#include "GLFWWrapper.hpp"
#include "SolarSystem.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "CommandAcceptor.hpp"
#include "GameEventsCommandProvider.hpp"
#include "CameraControlCommandProvider.hpp"

namespace oa {
namespace game {
class Game : public CommandAcceptor {
 public:
  Game();
  void init();
  void mainLoop();
  void stopGame();

 private:
  std::queue<Command *> commandQueue;
  std::vector<std::unique_ptr<CommandProvider>> providers;
  void initGLFW();
  void initSolarSystem();
  void initPlayer();
  bool isPlaying;
  void initCommandsInf();
  void processCommands();
  void addCommand(Command *);
  gl::GLFWWrapper *glfw;
  void deinit();
  SolarSystem solarSystem;
  render::Renderer renderer;
  render::Camera *camera;
};
}
}
