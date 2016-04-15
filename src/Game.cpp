#include <chrono>
#include <memory>
#include <thread>
#include "Game.hpp"
#include "PerspectiveCamera.hpp"

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

  auto cm = new CameraControlCommandProvider(this, this->camera);
  glfw->registerInputListener(cm);
  providers.push_back(std::unique_ptr<CommandProvider>(cm));
}

void Game::stopGame() { isPlaying = false; }

void Game::initGLFW() { glfw->init(); }

void Game::initSolarSystem() {
  solarSystem.createPlanets();
  // renderer.setSolarSystem(&solarSystem);
}

void Game::addCommand(Command *c) { commandQueue.push(c); }

void Game::processCommands() {
  while (commandQueue.size() > 0) {
    auto command = commandQueue.front();
    command->execute();
    commandQueue.pop();
    delete command;
  }
}
void Game::initPlayer() {
  camera = new render::PerspectiveCamera(glm::radians(45.0f), 4.0f / 3.0f, 1.0f,
                                         100.0f);
}

void Game::mainLoop() {
  while (isPlaying) {
    processCommands();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    renderer.render(solarSystem.getScene(), camera);
    glfw->endFrame();
  }

  deinit();
}

void Game::deinit() {}
}
}
