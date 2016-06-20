#include "GLFWWrapper.hpp"
#include <iostream>

namespace oa {
namespace gl {

GLFWWrapper::GLFWWrapper() : title("Orbital adventure") {}
GLFWWrapper::~GLFWWrapper() { glfwTerminate(); }

void GLFWWrapper::init() {
  initOpenGL();
  initInput();
}

GLFWwindow *GLFWWrapper::getWindow() { return window; }

void GLFWWrapper::getWindowSize(int &w, int &h) {
  w = width;
  h = height;
}

void GLFWWrapper::initOpenGL() {
  if (!glfwInit()) {
    this->errorCallback(100501, "GLFW didn't initialized");
    exit(EXIT_FAILURE);
  }
  glfwSetErrorCallback(this->errorCallback);
  determineOpenGLVersion();
  glew();
  int max;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
  std::cout << "Max texture size " << max << "\n";
  int texture_units;
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
  std::cout << "Max texture units per shader" << texture_units << "\n";
  int layers;
  glGetIntegerv(0x9317, &layers);
  std::cout << "Max texture units per shader" << layers << "\n";
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glDepthRange(0, 1000);
  printf("Shader lang: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void GLFWWrapper::glew() {
#ifndef __APPLE__
  std::cout << "INIT GLEW\n";
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
  glfwSetCharCallback(window, GLFWWrapper::charCallback);
  glfwSetScrollCallback(window, GLFWWrapper::mouseScrollCallback);
}

GLFWWrapper *GLFWWrapper::getInstance() {
  static GLFWWrapper GLFWWrapper;
  return &GLFWWrapper;
}

void GLFWWrapper::determineOpenGLVersion() {
  glfwDefaultWindowHints();
  for (int max = glfwVersionMajor; max != 0; --max) {
    if (max < glfwVersionMajor) glfwVersionMinor = 9;
    for (int min = glfwVersionMinor; min != 0; --min) {
      std::cout << "Try: " << max << "." << min << "\n";
      glfwWindowHint(GLFW_SAMPLES, samples);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, max);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      if (isFullScreen) {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(mode->width, mode->height, title.c_str(),
                                  monitor, NULL);
      } else {
        std::cout << "create window\n";
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
      }
      if (window) {
        glfwSetFramebufferSizeCallback(window,
                                       GLFWWrapper::windowResizeCallback);
      } else {
        continue;
      }

      glfwMakeContextCurrent(window);
      glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
      glfwVersionMajor = max;
      glfwVersionMinor = min;

      return;
    }
  }
}
void GLFWWrapper::windowResizeCallback(GLFWwindow *win, int width, int height) {
  auto inst = GLFWWrapper::getInstance();
  inst->width = width;
  inst->height = height;
  int fbWidth, fbHeight;
  glfwGetFramebufferSize(win, &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);
  inst->resolutionSlot(width, height);
  for (auto listener : inst->inputListeners) {
    listener->resize(width, height);
  }
}
void GLFWWrapper::errorCallback(int error, const char *description) {
  std::cerr << "[Error] " << error << " (" << description << ")\n";
}

void GLFWWrapper::addResolutionListener(
    ResolutionSignal::slot_function_type fn) {
  resolutionSlot.connect(fn);
}
void GLFWWrapper::charCallback(GLFWwindow *, unsigned int c) {
  GLFWWrapper *instance = getInstance();
  for (auto listener : instance->inputListeners) {
    listener->onChar(c);
  }
}
void GLFWWrapper::keyCallback(GLFWwindow *, int key, int scan, int action,
                              int mods) {
  GLFWWrapper *instance = getInstance();
  for (auto listener : instance->inputListeners) {
    if (action == GLFW_RELEASE) listener->onKeyUp(key, scan, mods);
    if (action == GLFW_PRESS) listener->onKeyDown(key, scan, mods);
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
