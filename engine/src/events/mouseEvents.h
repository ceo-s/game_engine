#pragma once
#include "event.h"

namespace engine {
namespace events {

namespace mouse {

class MouseEvent : public Event {
public:
  SET_CATEGORY(EventCategory::Mouse);
};

class MouseButtonEvent : public MouseEvent {
public:
  MouseButtonEvent(int button) : button_(button) {}

  const int &button = button_;
private:
  int button_;
};

class Move : public MouseEvent {
public:
  Move(float x, float y) : x(x), y(y) {}

  float &mouseX = x, &mouseY = y;

  SET_TYPE(EventType::MouseMove);

private:
  float x, y;
};

class Scroll : public MouseEvent {
public:
  Scroll(float x, float y) : x(x), y(y) {}

  float &offsetX = x, &offsetY = y;

  SET_TYPE(EventType::MouseScroll);

private:
  float x, y;
};

class ButtonClick : public MouseButtonEvent {
public:
  ButtonClick(int button) : MouseButtonEvent(button) {}

  SET_TYPE(EventType::MousePressed);
};

class ButtonRelease : public MouseButtonEvent {
public:
  ButtonRelease(int button) : MouseButtonEvent(button) {}

  SET_TYPE(EventType::MouseReleased);
};

}
}
}