#include "Gui.hpp"
#include <nanovg.h>
#include <iostream>
#include "GLFWWrapper.hpp"
#include "PayloadForm.hpp"
#include "RocketForm.hpp"
#include "StageForm.hpp"
#include "widgets/ImageButton.hpp"
#include "widgets/Panel.hpp"

namespace oa {
namespace gui {

Gui::~Gui() {}
Gui::Gui() {}

void Gui::initBuilderWindow() {
  using namespace nanogui;
  builderWindow = new Window(nanoguiScreen.get(), "");
  builderWindow->setVisible(false);
  builderWindow->setPosition(Vector2i(0, 0));
  //builderWindow->setFixedSize(Vector2i(200, 200));
  // Order important
  auto rocketButton = new Button(builderWindow, "Rocket design");
  initRocketWindow(builderWindow);
  auto stageButton = new Button(builderWindow, "Stage editor");
  initStageWindow(builderWindow);
  auto payloadButton = new Button(builderWindow, "Payload design");
  initPayloadWindow(builderWindow);
  new Label(builderWindow, "LABEL");

  builderWindow->setLayout(
      new BoxLayout(Orientation::Vertical, Alignment::Minimum, 0, 0));

  rocketButton->setCallback([this, rocketButton, stageButton, payloadButton]() {
    GuiTypes types[] = {STAGE, ROCKET, PAYLOAD};
    std::for_each(&types[0], &types[3], [&](auto ui) {
      if (uiWindows.count(ui)) {
        if (ui == ROCKET)
          uiWindows[ui]->show();
        else
          uiWindows[ui]->hide();
      }
    });
    stageButton->setVisible(true);
    payloadButton->setVisible(true);
    rocketButton->setVisible(false);
  });

  stageButton->setCallback([this, rocketButton, stageButton, payloadButton]() {
    GuiTypes types[] = {STAGE, ROCKET, PAYLOAD};
    std::for_each(&types[0], &types[3], [&](auto ui) {
      if (uiWindows.count(ui)) {
        if (ui == STAGE)
          uiWindows[ui]->show();
        else
          uiWindows[ui]->hide();
      }
    });
    stageButton->setVisible(false);
    payloadButton->setVisible(true);
    rocketButton->setVisible(true);
  });

  payloadButton->setCallback(
      [this, rocketButton, stageButton, payloadButton]() {
        GuiTypes types[] = {STAGE, ROCKET, PAYLOAD};
        std::for_each(&types[0], &types[3], [&](auto ui) {
          if (uiWindows.count(ui)) {
            std::cout << " found payload\n";
            if (ui == PAYLOAD) {
              uiWindows[ui]->show();
            } else
              uiWindows[ui]->hide();
          }
        });
        stageButton->setVisible(true);
        payloadButton->setVisible(false);
        rocketButton->setVisible(true);
      });
}

void Gui::initRocketWindow(nanogui::Widget *on) {
  auto ui = ROCKET;
  uiWindows[ui] = new RocketForm(on);
}
void Gui::initStageWindow(nanogui::Widget *on) {
  auto ui = STAGE;
  uiWindows[ui] = new StageForm(on);
}
void Gui::initPayloadWindow(nanogui::Widget *on) {
  auto ui = PAYLOAD;
  uiWindows[ui] = new PayloadForm(on);
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
  nanoguiScreen->performLayout(nanoguiScreen->nvgContext());
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
