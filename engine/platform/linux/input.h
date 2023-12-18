#pragma once
#include "src/input.h"

namespace engine {

class LinuxInput : public Input {
public:
  LinuxInput();

protected:
  bool isKeyPressed_(int keyCode) override;
  bool isMousePressed_(int button) override;

  std::pair<float, float> getMousePosition_() override;

};

}