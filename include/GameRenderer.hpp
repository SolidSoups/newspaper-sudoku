#pragma once

#include "sdl-common.hpp"

// wrapper for the SDL renderer
namespace ge {
class GameRenderer {
public:
  static SDL_Renderer *renderer;

  static float windowHeight;
  static float windowWidth;
};

} // namespace ge
