#pragma once
#include "std-common.hpp"
#include "vector2.hpp"

namespace ge {
class GameInput {
private:
  static vector2 mousePosition;
  static uint32_t mouseFlags;

public:
  static void poll();

public:
  static vector2 getMousePosition();
  static uint32_t getMouseFlags();
};
} // namespace ge
