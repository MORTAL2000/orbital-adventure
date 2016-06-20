#include "Gui.hpp"
#include <iostream>
#include "GLFWWrapper.hpp"

namespace oa {
namespace gui {

Gui::~Gui() {}
Gui::Gui() {}

void Gui::showView(std::string name) {}

void Gui::setRenderer(render::Renderer *r) {}

void Gui::render(float td) { nanoguiScreen->drawWidgets(); }

void Gui::setDimentions(int w, int h) {}
input::InputListener *Gui::getInputListener() { return inputListener.get(); }

enum test_enum { Item1 = 0, Item2, Item3 };
void Gui::init() {
  using namespace nanogui;
  nanoguiScreen = std::make_unique<Screen>();
  auto glfwWindow = gl::GLFWWrapper::getInstance()->getWindow();
  nanoguiScreen->initialize(glfwWindow, false);
  inputListener = std::make_unique<InputListener>(nanoguiScreen.get());
  // EXAMPLE

  bool bvar = true;
  int ivar = 12345678;
  double dvar = 3.1415926;
  float fvar = (float)dvar;
  std::string strval = "A string";
  test_enum enumval = Item2;
  Color colval(0.5f, 0.5f, 0.7f, 1.f);
  bool enabled = true;

  FormHelper *gui = new FormHelper(nanoguiScreen.get());
  ref<Window> window =
      gui->addWindow(Eigen::Vector2i(10, 10), "Form helper example");
  gui->addGroup("Basic types");
  gui->addVariable("bool", bvar);
  gui->addVariable("string", strval);

  gui->addGroup("Validating fields");
  gui->addVariable("int", ivar);
  gui->addVariable("float", fvar);
  gui->addVariable("double", dvar);

  gui->addGroup("Complex types");
  gui->addVariable("Enumeration", enumval, enabled)
      ->setItems({"Item 1", "Item 2", "Item 3"});
  gui->addVariable("Color", colval);

  gui->addGroup("Other widgets");
  gui->addButton("A button",
                 []() { std::cout << "Button pressed." << std::endl; });

  nanoguiScreen->setVisible(true);
  nanoguiScreen->performLayout();
  window->center();
}
}
}
