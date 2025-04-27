#include "Texture.hpp"
#include "ResourceManager.hpp"
#include "game-common.hpp"

namespace ge {
Texture::Texture(const char *filePath, SDL_FRect _src) {
  std::shared_ptr<SDL_Texture> tex(ResourceManager::loadTexture(filePath),
                                   SDL_DestroyTexture);
  texture = std::move(tex);
  if (!texture)
    ge::throw_runtime_error("Texture", "Failed to load texture '" +
                                           std::string(filePath) + "'");
  src = _src;
}

std::vector<Texture> Texture::CreateSheet(const char *filePath,
                                          const TextureSplitProperties &props) {
  std::shared_ptr<SDL_Texture> sharedTex(ResourceManager::loadTexture(filePath),
                                         SDL_DestroyTexture);
  if (!sharedTex)
    ge::throw_runtime_error("Texture", "Failed to load texture '" +
                                           std::string(filePath) + "'");

  // TODO: do some scaling maybe?
  // Set default sizes
  SDL_FRect src{0, 0, props.srcSizeX, props.srcSizeY};
  SDL_FRect dst{0, 0, props.srcSizeX, props.srcSizeY};

  size_t size = props.xSplitCount * props.ySplitCount;
  std::vector<Texture> textures;
  textures.reserve(size);

  for (int row = 0; row < props.ySplitCount; row++) {
    for (int col = 0; col < props.xSplitCount; col++) {
      src.x = col * props.srcSizeX;
      src.y = row * props.srcSizeY;
      textures.emplace_back(sharedTex, src);
    }
  }

  return textures;
}
} // namespace ge
