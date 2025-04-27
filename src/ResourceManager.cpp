#include "ResourceManager.hpp"
#include "GameEngine.hpp"
#include "GameRenderer.hpp"
#include "Texture.hpp"
#include "sdl-common.hpp"

SDL_Texture *ResourceManager::loadTexture(const char *filePath) {
  SDL_Surface *tmpSurface = IMG_Load(filePath);
  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(ge::GameRenderer::renderer, tmpSurface);
  SDL_DestroySurface(tmpSurface);
  return texture;
}

void ResourceManager::drawTexture(const ge::Texture &texture, SDL_FRect &dst) {
  SDL_RenderTexture(ge::GameRenderer::renderer, texture.texture.get(),
                    &texture.src, &dst);
}

void ResourceManager::drawTexture(SDL_Texture *tex, SDL_FRect &src,
                                  SDL_FRect &dst) {
  SDL_RenderTexture(ge::GameRenderer::renderer, tex, &src, &dst);
}
