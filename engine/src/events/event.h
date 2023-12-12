#pragma once
#define SET_TYPE(x) \
  static EventType getStaticType() {return x; };\
  EventType getType() override { return x; };\
  const char *getName() override { return #x; };\

#define SET_CATEGORY(x) EventCategory getCategory() override { return EventCategory(x); };

namespace engine {
namespace events {

enum class EventType : int {
  None = 0,
  WindowClose, WindowResize, WindowFocusIn, WindowFocusOut, WindowMove,
  AppTick, AppUpdate, AppRender,
  KeyPressed, KeyReleased, KeyTyped,
  MousePressed, MouseReleased, MouseMove, MouseScroll,
};

enum class EventCategory : int {
  None = 0,
  App = (1 << 0),
  Window = (1 << 1),
  Input = (1 << 2),
  Keyboard = (1 << 3),
  Mouse = (1 << 4),
  MouseButton = (1 << 5),
};

class Dispatcher;

class Event {
friend class Dispatcher;
public:
  Event() = default;
  virtual ~Event() = default;

protected:
  bool handled = false;

public:
  inline const bool isHandled() { return handled; }
  virtual EventCategory getCategory() = 0;
  virtual EventType getType() = 0;
  virtual const char *getName() = 0;

  inline bool isInCategory(EventCategory category) {
    return getCategory() == category;
  }
};


class Dispatcher {
public:
  template<typename T>
  using EventFn = std::function<bool(T &)>;

  Dispatcher(Event &event) : event(event) {}
  virtual ~Dispatcher() = default;

  template<typename T>
  bool dispatch(EventFn<T> func) {
    if (event.getType() == T::getStaticType()) {
      event.handled = func(*(T*)&event);
      return true;
    }
    return false;
  }

private:
  Event &event;
};

}
}
