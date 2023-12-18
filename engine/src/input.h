#pragma once

namespace engine {

class Input {
public:
  Input() = default;
  ~Input() = default;

  inline static bool isKeyPressed(int keyCode) { return instance->isKeyPressed_(keyCode); }
  inline static bool isMousePressed(int button) { return instance->isMousePressed_(button); }
  inline static std::pair<float, float> getMousePosition() {
    return instance->getMousePosition_();
  }

protected:
  static Input *instance;

  virtual bool isKeyPressed_(int keyCode) = 0;
  virtual bool isMousePressed_(int button) = 0;
  virtual std::pair<float, float> getMousePosition_() = 0;

};

}