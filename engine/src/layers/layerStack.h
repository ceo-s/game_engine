#pragma once
#include "src/pch/pch.h"
#include "layer.h"

namespace engine {
namespace layers {

class LayerStack {
public:
  LayerStack() {
    layerInsert = layers.begin();
  }
  ~LayerStack() {
    for (auto layer: layers) {
      delete layer;
    }
  }

  void pushLayer(Layer *layer) {
    layers.emplace(layerInsert, layer);

  }
  void popLayer(Layer *layer) {
    auto it = std::find(layers.begin(), layers.end(), layer);
    if (it != layers.end()) {
      layers.erase(it);
      --layerInsert;
    }
  }
  void pushOverlay(Layer *overlay) {
    layers.emplace_back(overlay);
  }
  void popOverlay(Layer *overlay) {
    auto it = std::find(layers.begin(), layers.end(), overlay);
    if (it != layers.end()) {
      layers.erase(it);
    }
  }

  std::vector<Layer*>::iterator begin() {return layers.begin(); };
  std::vector<Layer*>::iterator end() {return layers.end(); };
private:
  std::vector<Layer*> layers;
  std::vector<Layer*>::iterator layerInsert;
};

}
}