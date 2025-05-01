#include "AssetManager.hpp"
#include "GameObjects.hpp"
#include "GameRenderer.hpp"
#include "std-common.hpp"

namespace ge {
void UIToolbarNumber::onInit() {
  redNumberPlateTexture =
      AssetManager::retrieveGETextureCache("assets/red_number_plate.png");
  miniNumbersTextureSheet =
      AssetManager::retrieveGETextureSheetCache("assets/mini-numbers.png");
}

void UIToolbarNumber::update(const float &deltaTime) {
  accumulator += deltaTime;

  if (accumulator >= MAX_TIME)
    doDestroy();
}

void UIToolbarNumber::render() { drawAnimation(); }

void UIToolbarNumber::onClean() {}
void UIToolbarNumber::onDestroy() {}

double easeOutElastic(double x) {
    const double c4 = (2 * M_PI) / 3;

    if (x == 0) {
        return 0;
    } else if (x == 1) {
        return 1;
    } else {
        return std::pow(2, -10 * x) * std::sin((x * 10 - 0.75) * c4) + 1;
    }
}

void UIToolbarNumber::drawAnimation() {
  const float ORIGINAL_RED_PLATE_SIZE = 64;
  const float ORIGINAL_MINI_NUMBER_SIZE_X = 20;
  const float ORIGINAL_MINI_NUMBER_SIZE_Y = 32;

  float d = accumulator / MAX_TIME;
  float t = easeOutElastic(d);
  float sizingRatio = 1 + t * (SIZE_RATIO_TO - 1);

  // draw red plate
  float redPlateNewSize = ORIGINAL_RED_PLATE_SIZE * sizingRatio;
  float offsetAmount = ((redPlateNewSize - ORIGINAL_RED_PLATE_SIZE) / 2);
  SDL_FRect plateDst = {transform.position.x - offsetAmount,
                        transform.position.y - offsetAmount, redPlateNewSize,
                        redPlateNewSize};
  ge::GameRenderer::drawTexture(*redNumberPlateTexture, plateDst);

  // draw mini number
  float numberNewSizeX = ORIGINAL_MINI_NUMBER_SIZE_X * sizingRatio;
  float numberNewSizeY = ORIGINAL_MINI_NUMBER_SIZE_Y * sizingRatio;
  float offsetXAmount = (numberNewSizeX - ORIGINAL_MINI_NUMBER_SIZE_X) / 2;
  float offsetYAmount = (numberNewSizeY - ORIGINAL_MINI_NUMBER_SIZE_Y) / 2;
  SDL_FRect numberDst = {transform.position.x - offsetXAmount + 22,
                         transform.position.y - offsetYAmount + 16,
                         numberNewSizeX, numberNewSizeY};
  ge::GameRenderer::drawTexture(miniNumbersTextureSheet->textures[textureID],
                                numberDst);
}

} // namespace ge
