#include "GameRenderer.hpp"

#include "game-common.hpp"

// static
SDL_Renderer *ge::GameRenderer::renderer = nullptr;

float ge::GameRenderer::windowWidth = 0;
float ge::GameRenderer::windowHeight = 0;

void ge::GameRenderer::drawTexture(const ge::Texture &texture, SDL_FRect &dst) {
  if (!texture.texture) {
    ge::throw_runtime_error("AssetManager", "Texture is not initialized!");
  }
  SDL_RenderTexture(ge::GameRenderer::renderer, texture.texture.get(),
                    &texture.src, &dst);
}

void ge::GameRenderer::drawTexture(SDL_Texture *tex, SDL_FRect &src,
                                   SDL_FRect &dst) {
  SDL_RenderTexture(ge::GameRenderer::renderer, tex, &src, &dst);
}
