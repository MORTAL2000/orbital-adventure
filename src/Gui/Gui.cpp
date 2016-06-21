#include "Gui.hpp"
#include <nanovg.h>
#include <iostream>
#include "GLFWWrapper.hpp"
#include "ImageButton.hpp"

namespace oa {
namespace gui {

Gui::~Gui() {}
Gui::Gui() {}

void Gui::initBuilderWindow() {
  using namespace nanogui;
  builderWindow = new Widget(nanoguiScreen.get());
  builderWindow->setVisible(false);
  builderWindow->setPosition(Vector2i(0, 0));
  builderWindow->setFixedSize(Vector2i(200, 200));
  builderWindow->setLayout(new GroupLayout);
  new Label(builderWindow, "Builder");
}
void Gui::initScienceWindow() {
  using namespace nanogui;
  scienceWindow = new Widget(nanoguiScreen.get());
  scienceWindow->setVisible(false);
  scienceWindow->setPosition(Vector2i(0, 0));
  scienceWindow->setFixedSize(Vector2i(200, 200));
  scienceWindow->setLayout(new GroupLayout);
  new Label(scienceWindow, "Science", "sans-bold", 40);
}

void Gui::showView(std::string name) {}

void Gui::setRenderer(render::Renderer *r) {}

void Gui::render(float td) {
  using namespace nanogui;
  mainButtonsPanel->setPosition(Vector2i(0, height - 32));
  glGetError();
  nanoguiScreen->drawWidgets();
}

void Gui::setDimentions(int w, int h) {
  width = w;
  height = h;
}
input::InputListener *Gui::getInputListener() { return inputListener.get(); }

void Gui::init() {
  using namespace nanogui;
  nanoguiScreen = std::make_unique<Screen>();
  auto glfwWindow = gl::GLFWWrapper::getInstance()->getWindow();
  nanoguiScreen->initialize(glfwWindow, false);
  inputListener = std::make_unique<InputListener>(nanoguiScreen.get());
  initScienceWindow();
  initBuilderWindow();

  // EXAMPLE
  mainButtonsPanel = new Widget(nanoguiScreen.get());
  auto techButton = new ImageButton(mainButtonsPanel);
  auto builderButton = new ImageButton(mainButtonsPanel);
  builderButton->setFixedSize(Vector2i(32, 32));
  techButton->setFixedSize(Vector2i(32, 32));
  mainButtonsPanel->setPosition(Vector2i(50, 50));

  techButton->setImage(nvgCreateImage(nanoguiScreen->nvgContext(),
                                      "../data/gui/icons/science.png", 0));
  builderButton->setImage(nvgCreateImage(nanoguiScreen->nvgContext(),
                                         "../data/gui/icons/blueprint.png", 0));
  techButton->setCallback([&]() {
    auto sv = scienceWindow->visible();
    std::cout << "AAAA" << sv << "\n";
    scienceWindow->setVisible(!sv);
    builderWindow->setVisible(false);
  });
  builderButton->setCallback([&]() {
    auto bv = builderWindow->visible();
    scienceWindow->setVisible(false);
    builderWindow->setVisible(!bv);
  });

  mainButtonsPanel->setLayout(
      new BoxLayout(Orientation::Horizontal, Alignment::Maximum, 0, 2));

  nanoguiScreen->setVisible(true);
  nanoguiScreen->performLayout();
}
}
}
