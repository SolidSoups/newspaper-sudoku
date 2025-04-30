#pragma once

#include "sdl-common.hpp"
#include "std-common.hpp"
#include <memory>

namespace ge {
struct TextureProperties {
  float srcSizeX;
  float srcSizeY;
};

struct TextureSplitProperties : public TextureProperties {
  int xSplitCount = 1;
  int ySplitCount = 1;
};

struct Texture {
  std::shared_ptr<SDL_Texture> texture;
  SDL_FRect src;

  Texture() = default;
  Texture(const char *filePath, const TextureProperties &props);
  Texture(std::shared_ptr<SDL_Texture> tex, SDL_FRect _src)
      : texture(std::move(tex)), src(_src) {}
};

struct TextureSheet {
  std::shared_ptr<SDL_Texture> sharedTexture;
  std::vector<Texture> textures;
  TextureSheet(const char *filePath, const TextureSplitProperties &props);
};
} // namespace ge
