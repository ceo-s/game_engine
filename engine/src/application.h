#pragma once

namespace engine {

class Application {
public:
  Application() = default;
  ~Application() = default;
private:

public:
  void run();
};

Application *createApplication();
}