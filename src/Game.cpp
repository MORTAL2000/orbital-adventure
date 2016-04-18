#include <chrono>
#include <memory>
#include <thread>
#include "Game.hpp"
#include "SolarSystemCreator.hpp"
#include "engine/PerspectiveCamera.hpp"

#include <iostream>
namespace oa {
namespace game {
using namespace glm;

Game::Game() : isPlaying(true), glfw(oa::gl::GLFWWrapper::getInstance()) {}

void Game::init() {
  initGLFW();
  initSolarSystem();
  initPlayer();
  initCommandsInf();
}

void Game::initCommandsInf() {
  auto gm = new GameEventsCommandProvider(this, this);
  glfw->registerInputListener(gm);
  providers.push_back(std::unique_ptr<CommandProvider>(gm));

  auto cm = new CameraControlCommandProvider(this, &this->cameraManager);
  glfw->registerInputListener(cm);
  providers.push_back(std::unique_ptr<CommandProvider>(cm));
  auto fp = new PlanetInFocusCommandProvider(this, solarSystem.get(),
                                             &this->cameraManager);
  glfw->registerInputListener(fp);
  providers.push_back(std::unique_ptr<CommandProvider>(fp));
}

void Game::stopGame() { isPlaying = false; }

void Game::initGLFW() { glfw->init(); }

void Game::initSolarSystem() {
  SolarSystemCreator creator;
  creator.createSolarSystem("../data/planets.json");
  solarSystem = creator.getSolarSystem();
}

void Game::initPlayer() {
  // camera = new render::PerspectiveCamera(glm::radians(45.0f), 4.0f / 3.0f,
  // 1.0f,
  // 100.0f);
}

void Game::mainLoop() {
  while (isPlaying) {
    processCommands();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    renderer.render(solarSystem->getScene(), cameraManager.getCamera());
    glfw->endFrame();
  }

  deinit();
}

void Game::deinit() {}
}
}
