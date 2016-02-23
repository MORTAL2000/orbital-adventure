#include "Game.hpp"
#include <chrono>
#include <thread>

#include <iostream>
namespace oa {
namespace game {

Game::Game() : isPlaying(true), glfw(oa::gl::GLFWWrapper::getInstance()) {}

void Game::init() {
  initGLFW();
  initSolarSystem();
  initPlayer();
}

void Game::initGLFW() {
  glfw->init();
  glfw->registerInputListener(this);
}

void Game::initSolarSystem() {
  solarSystem.createPlanets();
  renderer.setSolarSystem(&solarSystem);
}

void Game::initPlayer() { std::cout << "init player\n"; }

void Game::onKeyDown(int key, int mods) {
  switch (key) {
    case GLFW_KEY_ESCAPE: {
      isPlaying = false;
      break;
    }
    default: { std::cout << "Key pressed " << key << " mods " << mods << "\n"; }
  }
}

void Game::mainLoop() {
  while (isPlaying) {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    renderer.render(camera.get());
    glfw->endFrame();
  }

  deinit();
}

void Game::deinit() {}
}
}
