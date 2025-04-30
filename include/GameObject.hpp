#pragma once

#include "Components.hpp"
#include "ECS.hpp"
#include <algorithm>

namespace ge {
class GameObject : public ecs::Entity {
public:
  GameObject() : transform(addComponent<ecs::Transform>()) {}
  ~GameObject() {}

public:
  virtual void onInit() = 0;
  virtual void update(const float &deltaTime) = 0;
  virtual void render() = 0;
  virtual void onClean() = 0;
  virtual void onDestroy() = 0;

public:
  void doInit() {
    // init for subclasses
    onInit();
    ;
    bIsInitialized = true;
    bIsClean = false;
    bIsDestroyed = false;
  }
  void doClean() {
    if (!bIsClean) {
      onClean();
      bIsClean = true;
    }
  }
  void doDestroy() {
    if (!bIsDestroyed) {
      onDestroy();
      bIsDestroyed = true;
    }
  }

  bool isInitialized() { return bIsInitialized; }
  bool isClean() { return bIsClean; }
  bool isDestroyed() { return bIsDestroyed; }

private:
  bool bIsClean = false;
  bool bIsDestroyed = false;
  bool bIsInitialized = false;

public:
  ecs::Transform &transform;
};

} // namespace ge
