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
using namespace std::chrono;

Game::Game()
    : simulatatedTime(std::chrono::system_clock::now()),
      oldTimePoint(std::chrono::system_clock::now()),
      isPlaying(true),
      glfw(oa::gl::GLFWWrapper::getInstance()) {}

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

  auto fp = new PlanetInFocusCommandProvider(this, solarSystem.get(),
                                             &this->cameraManager);
  glfw->registerInputListener(fp);
  processCommands();

  providers.push_back(std::unique_ptr<CommandProvider>(fp));

  auto cm = new CameraControlCommandProvider(this, &this->cameraManager);
  glfw->registerInputListener(cm);
  providers.push_back(std::unique_ptr<CommandProvider>(cm));
}

void Game::stopGame() { isPlaying = false; }

void Game::initGLFW() { glfw->init(); }

void Game::initSolarSystem() {
  SolarSystemCreator creator;
  creator.createSolarSystem("../data/planets.json");
  solarSystem = creator.getSolarSystem();
  cameraManager.setSolarSystem(solarSystem.get());
  solarSystem->setupUniformUpdaters(&cameraManager);
}

void Game::initPlayer() {
  // camera = new render::PerspectiveCamera(glm::radians(45.0f), 4.0f / 3.0f,
  // 1.0f,
  // 100.0f);
}

void Game::mainLoop() {
  while (isPlaying) {
    auto timePoint = std::chrono::system_clock::now();
    auto timeDiff = timePoint - oldTimePoint;
    if (timeMultiplier < 0.9e5) timeMultiplier = 60 * 60 * 24 * 7;
    // std::cout << timeDiff.count() / 1000000 << "\n";

    simulatatedTime +=
        system_clock::duration(uint64_t(timeDiff.count() * timeMultiplier));
    auto tt = system_clock::to_time_t(simulatatedTime);
    auto tm = localtime(&tt);
    solarSystem->updatePlanets(simulatatedTime);
    // std::cout << tm->tm_year << " " << tm->tm_mon << " " << tm->tm_mday <<
    // "\n";
    processCommands();

    renderer.render(solarSystem->getScene(), cameraManager.getCamera());
    glfw->endFrame();
    oldTimePoint = timePoint;
  }

  deinit();
}

void Game::deinit() {}
}
}
