#include "src/pch/pch.h"
#include "glad/glad.h"
#include "src/logger.h"
#include "window.h"

namespace engine {

static bool glfwInitialized = false;

Window *Window::create(const engine::WindowConfiguration &config) {
  return new LinuxWindow(config);
}

LinuxWindow::LinuxWindow(const WindowConfiguration &config) {
  init(config);
}

LinuxWindow::~LinuxWindow() {
  shutdown();
}

void LinuxWindow::init(const WindowConfiguration &config) {
  data.title = config.title;
  data.width = config.width;
  data.height = config.height;
  CORE_INFO("Creating window: Title = {0}. Size = {1}x{2}", data.title, data.height, data.width);

  if (!glfwInitialized) {
    if (!(glfwInitialized = glfwInit())) {
      CORE_ERROR("Could not initialize GLFW!");
    } else {
      glfwSetErrorCallback([](int errorCode, const char *description) {
        CORE_ERROR("GLFW error {0} : {1}", errorCode, description);
      });
    }
  }
  window = glfwCreateWindow(data.width, data.height, data.title, nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetWindowUserPointer(window, &data);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int w, int h) {
    Data &data = *(Data*)glfwGetWindowUserPointer(window);
    data.width = w;
    data.height = h;

    events::window::Resize event(w, h);
    data.callback(event);
  });

  glfwSetWindowCloseCallback(window, [](GLFWwindow *window) {
    Data &data = *(Data*)glfwGetWindowUserPointer(window);

    events::window::Close event;
    data.callback(event);
  });

  glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    Data &data = *(Data*)glfwGetWindowUserPointer(window);

    switch (action) {
      case GLFW_PRESS: {
        events::key::Pressed event{key, 0};
        data.callback(event);
        break;
      }
      case GLFW_RELEASE: {
        events::key::Released event{key};
        data.callback(event);
        break;
      }
      case GLFW_REPEAT: {
        events::key::Pressed event{key, 1};
        data.callback(event);
        break;
      }
    }

    glfwSetCharCallback(window, [](GLFWwindow *window, unsigned int keyCode) {
      Data &data = *(Data*) glfwGetWindowUserPointer(window);
      events::key::Typed event{(int)keyCode};
      data.callback(event);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
      Data &data = *(Data*)glfwGetWindowUserPointer(window);

      switch (action) {
        case GLFW_PRESS:
        {
          events::mouse::ButtonClick event{button};
          data.callback(event);
          break;
        }
        case GLFW_RELEASE:
        {
          events::mouse::ButtonRelease event{button};
          data.callback(event);
          break;
        }
      }

      glfwSetScrollCallback(window, [](GLFWwindow *window, double x, double y) {
        Data &data = *(Data*)glfwGetWindowUserPointer(window);
        events::mouse::Scroll event{(float)x, (float)y};
        data.callback(event);
      });

      glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
        Data &data = *(Data*)glfwGetWindowUserPointer(window);
        events::mouse::Move event{(float)x, (float)y};
        data.callback(event);
      });
    });
  });

}

void LinuxWindow::shutdown() {
  glfwDestroyWindow(window);
}

void LinuxWindow::onUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(window);
}

}