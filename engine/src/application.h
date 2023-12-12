#pragma once
#include "src/window.h"
#include "logger.h"
#include "layers/layers.h"

namespace engine {

class Application {
public:
  ~Application() = default;

private:
  static Application *instance;
  std::unique_ptr<Window> window;
  bool running = true;
  layers::LayerStack layerStack;

protected:
  Application();

public:
  void run();
  void onEvent(events::Event &event);
  bool onWindowClose(events::window::Close &event);
  void pushLayer(layers::Layer *layer);
  void pushOverlay(layers::Layer *layer);

  static inline Application &get() { return *instance; };
  static inline Window &getWindow() { return *instance->window; }

};

Application *createApplication();
}