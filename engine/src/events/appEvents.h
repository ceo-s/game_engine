#pragma once
#include "event.h"

namespace engine {
namespace events {

namespace app {

class AppEvent : public Event {
public:
  SET_CATEGORY(EventCategory::App);
};

class Tick : public AppEvent {
public:
  Tick() {}

  SET_TYPE(EventType::AppTick);
};

class Update : public AppEvent {
public:
  Update() {}

  SET_TYPE(EventType::AppUpdate);
};

class Render : public AppEvent {
public:
  Render() {}

  SET_TYPE(EventType::AppRender);
};

}
}
}