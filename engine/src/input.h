#pragma once


class Input {
public:
  Input();
  ~Input();

  static bool isKeyPressed(int keyCode) { return instance->isKeyPressed_(keyCode); }

protected:
  virtual bool isKeyPressed_(int keyCode) = 0;

private:
  static Input *instance;
};
