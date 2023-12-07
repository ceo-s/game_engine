#pragma once

//extern engine::Application *engine::createApplication();

int main(int argc, char *argv[]) {
  auto *app = engine::createApplication();
  app->run();
  delete app;
  return 0;
}
