#pragma once
#include "InputListener.hpp"
#include "GLFWWrapper.hpp"
#include "SolarSystem.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

namespace oa {
namespace game {
class Game : public input::InputListener {
 public:
  Game();
  void init();
  void mainLoop();

 private:
  void onKeyDown(int key, int mods);
  void initGLFW();
  void initSolarSystem();
  void initPlayer();
  bool isPlaying;
  gl::GLFWWrapper *glfw;
  void deinit();
  SolarSystem solarSystem;
  render::Renderer renderer;
  std::unique_ptr<render::Camera> camera;
};
}
}
