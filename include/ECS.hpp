#pragma once

#include "game-common.hpp"

// Forward declare
namespace ecs {
class Component;
class Entity;
} // namespace ecs

// ID Handling
using ComponentID = std::size_t;

inline ComponentID getComponentID() {
  static ComponentID lastID = 0;
  return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
  static ComponentID typeID = getComponentID();
  return typeID;
}

// Component
constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<ecs::Component *, maxComponents>;

namespace ecs {
class Component {
public:
  Entity *entity;
  virtual void init() {}

  virtual ~Component() {};
};
} // namespace ecs

// Entity
namespace ecs {
class Entity {
private:
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;
  ComponentArray componentArray;
  ComponentBitSet componentBitSet;

public:
  bool isActive() { return active; }
  void destroySelf() { active = false; }

  template <typename T> bool hasComponent() const {
    return componentBitSet[getComponentTypeID<T>()];
  }

  template <typename T, typename... TArgs> T &addComponent(TArgs &&...mArgs) {
    T *c(new T(std::forward<TArgs>(mArgs)...));
    c->entity = this;
    std::unique_ptr<Component> uPtr{c};
    components.emplace_back(std::move(uPtr));

    componentArray[getComponentTypeID<T>()] = c;
    componentBitSet[getComponentTypeID<T>()] = true;

    c->init();
    return *c;
  }

  template <typename T> T &getComponent() const {
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T *>(ptr);
  }
};
} // namespace ecs
