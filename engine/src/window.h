#pragma once
#include "pch/pch.h"
#include "events/events.h"

namespace engine {

struct WindowConfiguration {
  const char *title;
  uint32_t width;
  uint32_t height;
};

class Window {
public:
  using EventCallbackFn = std::function<void(events::Event&)>;
  virtual ~Window() = default;
  virtual void onUpdate() = 0;

  virtual GLFWwindow *getGlfwWindow() = 0;
  virtual void setEventCallback(const EventCallbackFn &callback) = 0;
  virtual uint32_t getWidth() = 0;
  virtual uint32_t getHeight() = 0;

  static Window *create(const WindowConfiguration &config = {"Default window", 1280, 720});
};

}