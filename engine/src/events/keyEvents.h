#pragma once
#include "event.h"

namespace engine {
namespace events {

namespace key {

class KeyEvent : public Event {
public:
  const int &keyCode = keyCode_;

  SET_CATEGORY((int) EventCategory::Keyboard | (int) EventCategory::Input);

protected:
  KeyEvent(int keyCode) : keyCode_(keyCode) {};
  int keyCode_ = 0;
};

class Pressed : public KeyEvent {
public:
  Pressed(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount_(repeatCount) {}

  const int &repeatCount = repeatCount_;

  SET_TYPE(EventType::KeyPressed);

private:
  int repeatCount_ = 0;
};

class Released : public KeyEvent {
public:
  Released(int keyCode) : KeyEvent(keyCode) {}

  SET_TYPE(EventType::KeyReleased);
};

class Typed : public KeyEvent {
public:
  Typed(int keyCode) : KeyEvent(keyCode) {}

  SET_TYPE(EventType::KeyTyped);
};

}
}
}