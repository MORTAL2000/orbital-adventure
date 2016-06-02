#include <chrono>
#include <memory>
#include <thread>
#include "Celestial/CurrentPlanetParams.hpp"
#include "Celestial/SolarSystemCreator.hpp"
#include "Game.hpp"
#include "engine/Filter.hpp"
#include "engine/LanguageUtils.hpp"
#include "engine/PerspectiveCamera.hpp"

#include <iostream>
namespace oa {
namespace game {
using namespace glm;
using namespace std::chrono;
using namespace utils;

Game::Game()
    : simulatatedTime(std::chrono::system_clock::now()),
      oldTimePoint(std::chrono::system_clock::now()),
      isPlaying(true),
      glfw(oa::gl::GLFWWrapper::getInstance()) {}

void Game::initTextureCreators() {}
void Game::init() {
  initGLFW();
  gui.init();
  initSolarSystem();
  initPlayer();
  initCommandsInf();
  initTextureCreators();
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

  glfw->registerInputListener(&guiListener);
  gui.setRenderer(&renderer);
  gui.load();
  //guiListener.setContext(gui.getContext());
  gui.showView("main");
}

void Game::stopGame() { isPlaying = false; }

void Game::initGLFW() { glfw->init(); }

void Game::prerender() {
  for (auto &cs : solarSystem->getPlanetMap()) {
    if (!cs.second->hasAtmosphere()) continue;
    render::UniformPtrHolder uh;
    for (auto &tc : textureCreators) {
      auto *params = new CurrentPlanetParams(cs.second.get());

      tc->clearUniformInstallers();
      tc->addUniformInstaller(params);
      renderer.render(tc.get(), &uh);
    }
    for (auto uname : uh.getUniformNames()) {  // transfer ownership
      cs.second->getMesh()->setUniformValue(uname, uh[uname]);
    }
  }
  int vpWidth, vpHeight;
  glfw->getWindowSize(vpWidth, vpHeight);
  renderer.setViewportDimentions(vpWidth, vpHeight);
}
void Game::initSolarSystem() {
  SolarSystemCreator creator;
  creator.withCamerManager(&cameraManager);
  creator.createSolarSystem("../data/planets.json");
  solarSystem = creator.getSolarSystem();
  for (auto *tc : creator.getTextureCreators())
    textureCreators.push_back(std::unique_ptr<render::TextureCreator>(tc));

  cameraManager.setSolarSystem(solarSystem.get());
  glfw->addResolutionListener([&](int width, int height) {
    renderer.setViewportDimentions(width, height);
    cameraManager.setNewWindowDimensions(width, height);
    gui.setDimentions(width, height);
  });
  for (auto f : creator.getRenderFilters()) {
    renderer.pushFilter(f);
  }
  prerender();
}

void Game::initPlayer() {}

int getI(int a){
  int r;
  glGetIntegerv(a, &r);
  return r;
}


void Game::mainLoop() {
  while (isPlaying) {
    auto timePoint = std::chrono::system_clock::now();
    auto timeDiff = timePoint - oldTimePoint;
    if (timeMultiplier < 0.9e5) timeMultiplier = 60 * 60;

    float timeDifff = duration_cast<Duration>(timeDiff).count();
    simulatatedTime +=
        system_clock::duration(uint64_t(timeDiff.count() * timeMultiplier));
    auto tt = system_clock::to_time_t(simulatatedTime);
    auto tm = localtime(&tt);
    solarSystem->updatePlanets(simulatatedTime);
    for (auto &p : providers) p->update(timeDifff);

    processCommands();
    auto camera =
        std::unique_ptr<render::Camera>(cameraManager.getCamera()->clone());
    std::cout << std::setprecision(17);

    renderer.unbindFramebuffer();
    renderer.clearColor();

    //renderer.render(solarSystem->getSkyboxScene(), camera.get());
    renderer.clearDepth();


    renderer.renderSorted(solarSystem->getScene(), camera.get());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gui.render(timeDifff);
    glDisable(GL_BLEND);


    glfw->endFrame();
    oldTimePoint = timePoint;
    //std::this_thread::sleep_for(2s);
  }
  deinit();
}

void Game::deinit() {}
}
}
