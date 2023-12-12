#pragma once
#include "layer.h"
#include "src/events/events.h"

namespace engine {
namespace layers {

class ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();
  void onAttach() override;
  void onDetach() override;
  void onUpdate() override;
  void onEvent(events::Event &event) override;

private:
  bool show;
  float time;

  bool onMouseButtonClick(events::mouse::ButtonClick &event);
  bool onMouseButtonReleased(events::mouse::ButtonRelease &event);
  bool onMouseMoved(events::mouse::Move &event);
  bool onMouseScrolled(events::mouse::Scroll &event);
  bool onKeyPressed(events::key::Pressed &event);
  bool onKeyReleased(events::key::Released &event);
  bool onKeyTyped(events::key::Typed &event);
  bool onWindowResize(events::window::Resize &event);

public:

};

}
}