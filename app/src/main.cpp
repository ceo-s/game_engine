#include <iostream>
#include "engine.h"

class ExampleLayer : public engine::layers::Layer {
  void onUpdate() override {
    LOG_INFO("Balls");
  }

  void onEvent(engine::events::Event &event) override {
    LOG_ERROR("Ev {0}", event.getName());
  }
};

class Sandbox : public engine::Application {
public:
  Sandbox() {
//    pushLayer(new ExampleLayer);
    pushLayer(new engine::layers::ImGuiLayer);
  }
};

engine::Application *engine::createApplication() {
  return new Sandbox();
}