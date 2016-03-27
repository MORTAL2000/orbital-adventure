#include "GLFWWrapper.hpp"
#include <iostream>

namespace oa {
namespace gl {

GLFWWrapper::GLFWWrapper() : title("Orbital adventure") {}
GLFWWrapper::~GLFWWrapper() {
  glDeleteVertexArrays(1, &VertexArrayID);
  glfwTerminate();
}

void GLFWWrapper::init() {
  initOpenGL();
  initInput();
}

void GLFWWrapper::genAttribArrays() {
  std::cout << "gen Attrib arrays\n";
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  std::cout << "GGG " << VertexArrayID << "\n";
}

void GLFWWrapper::initOpenGL() {
  if (!glfwInit()) {
    this->errorCallback(100501, "GLFW didn't initialized");
    exit(EXIT_FAILURE);
  }
  glfwSetErrorCallback(this->errorCallback);
  determineOpenGLVersion();
  genAttribArrays();
  glClearColor(0.1, 0.0, 0.4, .0);
  // glEnable(GL_DEPTH_TEST);
  // glDepthFunc(GL_LESS);
  // glEnable(GL_CULL_FACE);
  printf("Shader lang: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
  glew();
}

void GLFWWrapper::glew() {
#ifndef __APPLE__
  if (!glewInitialized) {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
      return;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    glewInitialized = true;
  }
#endif
}
void GLFWWrapper::initInput() {
  glfwSetCursorPosCallback(window, GLFWWrapper::mouseMoveCallback);
  glfwSetMouseButtonCallback(window, GLFWWrapper::mouseKeyCallback);
  glfwSetKeyCallback(window, GLFWWrapper::keyCallback);
  glfwSetScrollCallback(window, GLFWWrapper::mouseScrollCallback);
  std::cout << "input glewInitialized \n";
}

GLFWWrapper *GLFWWrapper::getInstance() {
  static GLFWWrapper GLFWWrapper;
  return &GLFWWrapper;
}

void GLFWWrapper::determineOpenGLVersion() {
  for (int max = glfwVersionMajor; max != 0; --max) {
    if (max < glfwVersionMajor) glfwVersionMinor = 9;
    for (int min = glfwVersionMinor; min != 0; --min) {
      std::cout << "Try: " << max << "." << min << "\n";
      glfwWindowHint(GLFW_SAMPLES, samples);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, max);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
      // if(glfwVersionMajor * 10 + glfwVersionMinor > 32)
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      GLFWmonitor *monitor = glfwGetPrimaryMonitor();
      const GLFWvidmode *mode = glfwGetVideoMode(monitor);
      if (isFullScreen)
        window = glfwCreateWindow(mode->width, mode->height, title.c_str(),
                                  monitor, NULL);
      else
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
      if (!window) continue;

      glfwMakeContextCurrent(window);
      glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
      std::cout << "determined\n";
      glfwVersionMajor = max;
      glfwVersionMinor = min;
      return;
    }
  }
}
void GLFWWrapper::errorCallback(int error, const char *description) {
  std::cerr << "[Error] " << error << " (" << description << ")\n";
}

void GLFWWrapper::keyCallback(GLFWwindow *, int key, int scan, int action,
                              int mods) {
  GLFWWrapper *instance = getInstance();
  for (auto listener : instance->inputListeners) {
    if (action == GLFW_RELEASE) listener->onKeyUp(key, mods);
    if (action == GLFW_PRESS) listener->onKeyDown(key, mods);
  }
}

void GLFWWrapper::mouseMoveCallback(GLFWwindow *, double x, double y) {
  GLFWWrapper *instance = getInstance();
  for (auto listener : instance->inputListeners) {
    listener->onMouseMove(glm::vec2(x, y));
  }
}

void GLFWWrapper::mouseKeyCallback(GLFWwindow *, int key, int action,
                                   int mods) {
  GLFWWrapper *instance = getInstance();
  for (auto listener : instance->inputListeners) {
    if (action == GLFW_RELEASE)
      listener->onMouseUp(key, mods);
    else
      listener->onMouseDown(key, mods);
  }
}

void GLFWWrapper::mouseScrollCallback(GLFWwindow *, double w, double v) {
  GLFWWrapper *instance = getInstance();
  for (auto listener : instance->inputListeners) {
    listener->onScroll(w, v);
  }
}

void GLFWWrapper::registerInputListener(oa::input::InputListener *listener) {
  inputListeners.push_back(listener);
}

void GLFWWrapper::endFrame() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}
}
}
