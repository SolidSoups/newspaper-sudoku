#include "AssetManager.hpp"
#include "GameObjects.hpp"
#include "GameRenderer.hpp"
#include "game-common.hpp"

namespace ge {
void UIToolbar::onInit() {
  uiToolbarBackdropTexture = AssetManager::retrieveGETextureCache(
      "assets/numbers_toolbar_ui_backdrop.png");
  miniNumbersTextureSheet =
      AssetManager::retrieveGETextureSheetCache("assets/mini-numbers.png");

  ge::log_msg("UIToolbar", "Initialized!");
  transform.position = {0, (768 - 640) / 2.0f};
}
void UIToolbar::update(const float &deltaTime) {}
void UIToolbar::render() {
  using namespace assetDefaults;
  // draw toolbar backdrop
  SDL_FRect toolbarDst = {transform.position.x, transform.position.y, 64, 640};
  ge::GameRenderer::drawTexture(*uiToolbarBackdropTexture, toolbarDst);

  SDL_FRect numberDst = {22, toolbarDst.y + 16, 20, 32};
  for (int i = 1; i <= 9; i++) {
    NumberTextureID texID = static_cast<NumberTextureID>(i);
    ge::GameRenderer::drawTexture(miniNumbersTextureSheet->textures[texID],
                                  numberDst);
    numberDst.y += 16 * 4;
  }
}

void UIToolbar::onClean() {}
void UIToolbar::onDestroy() {}

void UIToolbar::drawToolbar() {}
} // namespace ge
