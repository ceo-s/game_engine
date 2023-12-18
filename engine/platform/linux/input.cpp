#include "input.h"
#include <GLFW/glfw3.h>
#include "src/application.h"

namespace engine {

Input *Input::instance = new LinuxInput;

LinuxInput::LinuxInput() {
  if (instance != nullptr) {
    CORE_ERROR("Creating multiple instances of LinuxInput!");
    exit(1);
  }
  instance = this;
}

bool LinuxInput::isKeyPressed_(int keyCode) {
  auto window = static_cast<GLFWwindow *>(Application::getWindow().getGlfwWindow());
  int state = glfwGetKey(window, keyCode);
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool LinuxInput::isMousePressed_(int button) {
  auto window = static_cast<GLFWwindow *>(Application::getWindow().getGlfwWindow());
  int state = glfwGetMouseButton(window, button);
  return state == GLFW_PRESS;
}

std::pair<float, float> LinuxInput::getMousePosition_() {
  auto window = static_cast<GLFWwindow *>(Application::getWindow().getGlfwWindow());
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  return { x, y };
}

}