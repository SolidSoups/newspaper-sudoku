#pragma once

#include "Texture.hpp"
#include "sdl-common.hpp"
#include <unordered_map>

class AssetManager {
private:
  static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
      textureCache;
  static std::unordered_map<std::string, std::shared_ptr<ge::Texture>>
      geTextureCache;

public:
  // Load a texture from a filepath
  static std::shared_ptr<SDL_Texture> loadTexture(const char *filePath);

public:
  //  caches ge::Texture with the filePath as an index
  static ge::Texture& createGETexture(const char* filepath, const SDL_FRect& src);
  // Retrieves a cacehed ge::Texture with the filePath as an index
  static ge::Texture &retrieveGETexture(const char *filePath);
};
