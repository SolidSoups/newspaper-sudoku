#pragma once

#include "ECS.hpp"
#include "tools/vector2.hpp"

namespace ecs {
class Transform : public Component {
public:
  Transform() {}
  virtual ~Transform() {}

public:
  vector2 position;

  void init() override {
    position.x = 0.0f;
    position.y = 0.0f;
  }
};
} // namespace ecs
