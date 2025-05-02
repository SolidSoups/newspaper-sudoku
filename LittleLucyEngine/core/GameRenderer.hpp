#pragma once

#include "renderer/Texture.hpp"
struct SDL_Renderer;

// wrapper for the SDL renderer
namespace ge {
class GameRenderer {
public:
  static SDL_Renderer *renderer;

  static float windowHeight;
  static float windowWidth;

  // Draw a texture with a dst
  static void drawTexture(const ge::Texture &texture, SDL_FRect &dst);
  // Draw a raw SDL_Texture with a src and dst
  static void drawTexture(SDL_Texture *tex, SDL_FRect &src, SDL_FRect &dst);
};

} // namespace ge
