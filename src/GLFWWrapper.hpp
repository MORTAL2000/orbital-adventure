#pragma once

#ifndef __APPLE_CC__
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#endif
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "InputListener.hpp"

namespace oa {
namespace gl {
class GLFWWrapper final {
 public:
  void init();  // Init opengl, scene, and everything;
  static GLFWWrapper *getInstance();
  void registerInputListener(oa::input::InputListener *);
  void endFrame();
  ~GLFWWrapper();

 private:
  int glfwVersionMajor = 3;
  int glfwVersionMinor = 2;
  int samples = 4;
  bool isFullScreen = false;
  bool glewInitialized = false;
  std::string title;
  int width = 800;
  int height = 600;
  GLuint VertexArrayID;
  GLFWwindow *window = nullptr;
  std::vector<oa::input::InputListener *> inputListeners;
  GLFWWrapper();
  void initOpenGL();
  void initInput();
  void glew();
  void genAttribArrays();

  void determineOpenGLVersion();

  static void errorCallback(int error, const char *description);
  static void keyCallback(GLFWwindow *, int key, int scan, int action,
                          int mods);
  static void mouseMoveCallback(GLFWwindow *, double x, double y);
  static void mouseKeyCallback(GLFWwindow *, int key, int action, int mods);
  static void mouseScrollCallback(GLFWwindow *, double x, double y);
};
}
}
