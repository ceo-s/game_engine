#pragma once
#include "src/window.h"
#include "GLFW/glfw3.h"

namespace engine {

class LinuxWindow : public Window{
public:
  LinuxWindow(const WindowConfiguration &config);
  ~LinuxWindow();

  void onUpdate() override;

  GLFWwindow * getGlfwWindow() override { return window; }
  inline void setEventCallback(const Window::EventCallbackFn &callback) override { data.callback = callback; }
  inline uint32_t getWidth() override { return data.width; }
  inline uint32_t getHeight() override { return data.height; }

private:
  virtual void init(const WindowConfiguration &config);
  virtual void shutdown();

  GLFWwindow *window;

  struct Data {
    const char *title;
    uint32_t width;
    uint32_t height;

    Window::EventCallbackFn callback;
  };

  Data data;

};

}