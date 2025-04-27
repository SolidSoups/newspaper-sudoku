#pragma once

#include "sdl-common.hpp"
#include "std-common.hpp"

namespace ge {
struct TextureSplitProperties {
  float srcSizeX;
  float srcSizeY;
  int xSplitCount = 1;
  int ySplitCount = 1;
};

struct Texture {
  std::shared_ptr<SDL_Texture> texture;
  SDL_FRect src;

  Texture() = default;
  Texture(const char *filePath, SDL_FRect _src);
  Texture(std::shared_ptr<SDL_Texture> tex, SDL_FRect _src)
      : texture(std::move(tex)), src(_src) {}

  static std::vector<Texture> CreateSheet(const char *filePath,
                                          const TextureSplitProperties &props);
};
} // namespace ge
