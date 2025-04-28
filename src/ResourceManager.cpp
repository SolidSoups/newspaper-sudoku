#include "AssetManager.hpp"
#include "GameRenderer.hpp"
#include "Texture.hpp"
#include "game-common.hpp"

SDL_Texture *AssetManager::loadTexture(const char *filePath) {
  SDL_Surface *tmpSurface = IMG_Load(filePath);
  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(ge::GameRenderer::renderer, tmpSurface);
  SDL_DestroySurface(tmpSurface);
  return texture;
}

