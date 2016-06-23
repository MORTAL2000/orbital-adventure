#pragma once
#undef NDEBUG
#include <nanogui/nanogui.h>
#include <map>
#include "../engine/Renderer.hpp"
#include "InputListener.hpp"

namespace oa {
namespace gui {
class Gui {
  enum GuiTypes {
    STAGE,
    ROCKET,
    PAYLOAD,
    STAGE_FORM,
    STAGE_ENGINE,
    STAGE_TANKS,
    STAGE_STRUCTURE,
    STAGE_DEVICES,
    ROCKET_DESIGN,
    PAYLOD_FORM,
    PAYLOAD_TANKS,
    PAYLOAD_DEVICES
  };
  std::map<std::string, std::string> viewMap;
  const std::string guiRendererTarget;
  std::unique_ptr<nanogui::Screen> nanoguiScreen;
  std::unique_ptr<InputListener> inputListener;
  int width, height;
  nanogui::Widget *mainButtonsPanel;
  nanogui::Widget *builderWindow;
  nanogui::Widget *scienceWindow;
  std::map<GuiTypes, nanogui::Widget *> uiWindows;

  void initBuilderWindow();
  void initScienceWindow();

  void initRocketWindow(nanogui::Widget *);
  void initStageWindow(nanogui::Widget *);
  void initPayloadWindow(nanogui::Widget *);

  void initStageTanksindow();
  void initStageEngineWindow();
  void initStageStructureWindow();
  void initStageDevices();

 public:
  ~Gui();
  Gui();
  void init();
  void setRenderer(render::Renderer *renderer);
  input::InputListener *getInputListener();
  void showView(std::string name);
  void render(float timeDiff);
  void setDimentions(int, int);
};
}
}
