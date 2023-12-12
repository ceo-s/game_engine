#pragma once
#include "logger.h"
#include "events/keyEvents.h"

int main(int argc, char *argv[]) {
  {
    using namespace engine;
    using namespace engine::events;
    Logger::init();
    mouse::Move mme{1, 2};
    mouse::ButtonClick mce{1};
    mouse::ButtonRelease mre{1};
    mouse::Scroll mse{1, 2};
    key::Pressed kpe{1, 10};
    key::Released kre{1};
    app::Tick ate;
    app::Update aue;
    app::Render are;
    window::Resize wre{1, 2};
    window::Close wce;


    Event *evArr[11] = {
      &mme, &mce, &mre, &mse, &kpe,
      &kre, &ate, &aue, &are, &wre,
      &wce,
    };
    CORE_INFO("Opengl version")
  }
  auto *app = engine::createApplication();
  app->run();
  delete app;
  return 0;
}
