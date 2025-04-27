#pragma once

#include "Texture.hpp"
#include "sdl-common.hpp"

class ResourceManager {
public:
  // Load a texture from a filepath
  static SDL_Texture *loadTexture(const char *filePath);
  // Draw a texture with a dst
  static void drawTexture(const ge::Texture &texture, SDL_FRect &dst);
  // Draw a raw SDL_Texture with a src and dst
  static void drawTexture(SDL_Texture *tex, SDL_FRect &src, SDL_FRect &dst);
};
