#pragma once
#include "src/events/event.h"

namespace engine {
namespace layers {

class Layer {
public:
  Layer(const char *name = "Layer") : name(name) {}
  virtual ~Layer() = default;

  virtual void onAttach() {}
  virtual void onDetach() {}
  virtual void onUpdate() {}
  virtual void onEvent(events::Event &event) {}

  inline const char *getName() { return name; }

protected:
  const char *name;
};

}
}