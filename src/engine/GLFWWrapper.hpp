#pragma once

#ifndef __APPLE_CC__
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#endif
#include <GLFW/glfw3.h>
#include <boost/signals2.hpp>
#include <string>
#include <vector>

#include "InputListener.hpp"

namespace oa {
namespace gl {
class GLFWWrapper final {
  typedef boost::signals2::signal<void(int, int)> ResolutionSignal;

 public:
  void init();  // Init opengl, scene, and everything;
  static GLFWWrapper *getInstance();

  void registerInputListener(oa::input::InputListener *);
  void addResolutionListener(ResolutionSignal::slot_function_type fn);
  void endFrame();
  void getWindowSize(int &width, int &height);
  GLFWwindow *getWindow();
  ~GLFWWrapper();

 private:
  int glfwVersionMajor = 4;
  int glfwVersionMinor = 1;
  int samples = 4;
  bool isFullScreen = false;
  bool glewInitialized = false;
  std::string title;
  int width = 800;
  int height = 600;
  GLFWwindow *window = nullptr;
  std::vector<oa::input::InputListener *> inputListeners;
  ResolutionSignal resolutionSlot;
  GLFWWrapper();
  void initOpenGL();
  void initInput();
  void glew();
  void determineOpenGLVersion();

  static void errorCallback(int error, const char *description);
  static void keyCallback(GLFWwindow *, int key, int scan, int action,
                          int mods);
  static void mouseMoveCallback(GLFWwindow *, double x, double y);
  static void mouseKeyCallback(GLFWwindow *, int key, int action, int mods);
  static void mouseScrollCallback(GLFWwindow *, double x, double y);
  static void windowResizeCallback(GLFWwindow *, int width, int height);
  static void cursorPosCallback(GLFWwindow *, double, double);
  static void charCallback(GLFWwindow *, unsigned int);
  static void dropCallback(GLFWwindow *, int count, const char **filenames);
};
}
}
