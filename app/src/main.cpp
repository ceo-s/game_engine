#include <iostream>
#include "engine.h"

class Sandbox : public engine::Application {

};

engine::Application *engine::createApplication() {
  return new Sandbox();
}