#include "imguiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "src/application.h"

#define IMGUI_BIND_FUNC(x) std::bind_front(&ImGuiLayer::x, this)

namespace engine {
namespace layers {

ImGuiLayer::ImGuiLayer() : Layer("ImGui layer") {

}

ImGuiLayer::~ImGuiLayer() {

}

void ImGuiLayer::onAttach() {
  Layer::onAttach();

  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  Application &app = Application::get();
  ImGui_ImplGlfw_InitForOpenGL(app.getWindow().getGlfwWindow(), true);
  ImGui_ImplOpenGL3_Init();
  time = (float)glfwGetTime();
}

void ImGuiLayer::onDetach() {
  Layer::onDetach();
}

void ImGuiLayer::onUpdate() {
  Layer::onUpdate();

  ImGuiIO &io = ImGui::GetIO();
  auto newTime = (float)glfwGetTime();
  io.DeltaTime = time > 0. ? (newTime - time) : (1.0 / 60.0);

  Application &app = Application::get();
  io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());
  show = true;

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::ShowDemoWindow(&show);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::onEvent(events::Event &event) {
  Layer::onEvent(event);
  events::Dispatcher dispatcher {event};
  dispatcher.dispatch<events::mouse::ButtonClick>(IMGUI_BIND_FUNC(onMouseButtonClick));
  dispatcher.dispatch<events::mouse::ButtonRelease>(IMGUI_BIND_FUNC(onMouseButtonReleased));
  dispatcher.dispatch<events::mouse::Move>(IMGUI_BIND_FUNC(onMouseMoved));
  dispatcher.dispatch<events::mouse::Scroll>(IMGUI_BIND_FUNC(onMouseScrolled));
  dispatcher.dispatch<events::key::Pressed>(IMGUI_BIND_FUNC(onKeyPressed));
  dispatcher.dispatch<events::key::Released>(IMGUI_BIND_FUNC(onKeyReleased));
  dispatcher.dispatch<events::key::Typed>(IMGUI_BIND_FUNC(onKeyTyped));
  dispatcher.dispatch<events::window::Resize>(IMGUI_BIND_FUNC(onWindowResize));

}

bool ImGuiLayer::onMouseButtonClick(events::mouse::ButtonClick &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[event.button] = true;
  return false;
}

bool ImGuiLayer::onMouseButtonReleased(events::mouse::ButtonRelease &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[event.button] = false;
  return false;
}

bool ImGuiLayer::onMouseMoved(events::mouse::Move &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.MousePos = ImVec2(event.mouseX, event.mouseY);
  return false;
}

bool ImGuiLayer::onMouseScrolled(events::mouse::Scroll &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseWheelH += event.offsetX;
  io.MouseWheel += event.offsetY;
  return false;
}

bool ImGuiLayer::onKeyPressed(events::key::Pressed &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[event.keyCode] = true;

  io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL | GLFW_KEY_RIGHT_CONTROL];
  io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT | GLFW_KEY_RIGHT_SHIFT];
  io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT | GLFW_KEY_RIGHT_ALT];
  io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER | GLFW_KEY_RIGHT_SUPER];
  return false;
}

bool ImGuiLayer::onKeyReleased(events::key::Released &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[event.keyCode] = true;
  return false;
}

bool ImGuiLayer::onKeyTyped(events::key::Typed &event) {
  ImGuiIO &io = ImGui::GetIO();
  int keyCode = event.keyCode;

  if (keyCode > 0 && keyCode < 0x10000)
    io.AddInputCharacter((unsigned short)keyCode);

  return false;
}

bool ImGuiLayer::onWindowResize(events::window::Resize &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.DisplaySize = ImVec2(event.width, event.height);
  io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
  glViewport(0, 0, event.width, event.height);
  return false;
}
}
}