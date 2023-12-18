#include "src/pch/pch.h"
#include "application.h"
#include "input.h"
#include "glm/glm.hpp"

#define BIND_FUNC(x) std::bind_front(&Application::x, this)

namespace engine {

Application *Application::instance = nullptr;

Application::Application() {

  if (instance != nullptr) {
    CORE_ERROR("Creating multiple instances of Application!");
    exit(1);
  }

  instance = this;
  window = std::unique_ptr<Window>(Window::create());
  window->setEventCallback(BIND_FUNC(onEvent));
}


void Application::onEvent(events::Event &event) {
  events::Dispatcher dispatcher{event};
  dispatcher.dispatch<events::window::Close>(BIND_FUNC(onWindowClose));
  CORE_INFO("This is event - {0}", event.getName());

  for (auto it = layerStack.end(); it != layerStack.begin(); ) {
    (*(--it))->onEvent(event);
    if (event.isHandled()) break;
  }

}

void Application::run() {
  CORE_INFO("Running application");
  while (running) {
    glClearColor(0.2, 0.3, 1., 1.);
    glClear(GL_COLOR_BUFFER_BIT);
    auto [x, y] = Input::getMousePosition();

    CORE_DEBUG("MousePos<{0}, {1}>", x, y);
    for (auto layer: layerStack) {
      layer->onUpdate();
    }
    window->onUpdate();
  }
}

bool Application::onWindowClose(events::window::Close &event) {
  running = false;
  return false;
}

void Application::pushLayer(layers::Layer *layer) {
  layerStack.pushLayer(layer);
  layer->onAttach();
}

void Application::pushOverlay(layers::Layer *layer) {
  layerStack.pushOverlay(layer);
  layer->onAttach();
}


}