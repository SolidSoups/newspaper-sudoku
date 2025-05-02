#include "core/renderer/Texture.hpp"
#include "core/AssetManager.hpp"
#include "tools/logger.hpp"

namespace ge {
// Texture constructor
Texture::Texture(const char *filePath, const TextureProperties &props) {
  std::shared_ptr<SDL_Texture> tex = AssetManager::loadTexture(filePath);
  texture = std::move(tex);
  if (!texture)
    ge::throw_runtime_error("Texture", "Failed to load texture '" +
                                           std::string(filePath) + "'");
  src = SDL_FRect{0, 0, props.srcSizeX, props.srcSizeY};
  SDL_SetTextureScaleMode(texture.get(), SDL_SCALEMODE_NEAREST);
}

// TextureSheet constructor
TextureSheet::TextureSheet(const char *filePath,
                           const TextureSplitProperties &props) {
  sharedTexture = AssetManager::loadTexture(filePath);
  if (!sharedTexture) {
    ge::throw_runtime_error("texture", "failed to load texture '" +
                                           std::string(filePath) + "'");
  }

  SDL_SetTextureScaleMode(sharedTexture.get(), SDL_SCALEMODE_NEAREST);

  // TODO: do some scaling maybe?
  // Set default sizes
  SDL_FRect src{0, 0, props.srcSizeX, props.srcSizeY};
  SDL_FRect dst{0, 0, props.srcSizeX, props.srcSizeY};

  size_t size = props.xSplitCount * props.ySplitCount;
  textures.clear();
  textures.reserve(size);

  for (int row = 0; row < props.ySplitCount; row++) {
    for (int col = 0; col < props.xSplitCount; col++) {
      src.x = col * props.srcSizeX;
      src.y = row * props.srcSizeY;
      textures.emplace_back(sharedTexture, src);
    }
  }
}
} // namespace ge
