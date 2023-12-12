#pragma once
#include "event.h"

namespace engine {
namespace events {

namespace window {

class WindowEvent : public Event {
public:
  SET_CATEGORY((int) EventCategory::Window | (int) EventCategory::App);
};

class Resize : public WindowEvent {
public:
  Resize(int width, int height) : w(width), h(height) {};
  SET_TYPE(EventType::WindowResize);
  const int &width = w, &height = h;

private:
  int w, h;

};

class Close : public WindowEvent {
public:
  Close() {}
  SET_TYPE(EventType::WindowClose);
};

}
}
}