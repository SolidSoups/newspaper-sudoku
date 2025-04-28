#include "AssetManager.hpp"
#include "GameRenderer.hpp"
#include "SDL3/SDL_render.h"
#include "Texture.hpp"
#include "game-common.hpp"
#include <unordered_map>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
    AssetManager::textureCache{};
std::unordered_map<std::string, std::shared_ptr<ge::Texture>>
    AssetManager::geTextureCache;

std::shared_ptr<SDL_Texture> AssetManager::loadTexture(const char *filePath) {
  // retrieve cache if available
  if (textureCache.find(filePath) != textureCache.end()) {
    return textureCache[filePath];
  }

  // otherwise create texture and cache it
  SDL_Surface *tmpSurface = IMG_Load(filePath);
  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(ge::GameRenderer::renderer, tmpSurface);
  SDL_DestroySurface(tmpSurface);

  // cache
  std::shared_ptr<SDL_Texture> ptr(texture, SDL_DestroyTexture);
  textureCache[filePath] = ptr;

  return ptr;
}

ge::Texture& AssetManager::createGETexture(const char* filePath, const SDL_FRect& src){
  ge::Texture* newTex = new ge::Texture(filePath, src);
  std::shared_ptr<ge::Texture> ptr(newTex); 
  geTextureCache[filePath] = ptr;
  return *ptr;
}

ge::Texture &AssetManager::retrieveGETexture(const char *filePath){
  if(geTextureCache.find(filePath) == geTextureCache.end())
    ge::throw_runtime_error("AssetManager", "Could not find texture in cache!");
  return *geTextureCache.at(filePath);
}
