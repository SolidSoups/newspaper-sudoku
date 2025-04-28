#include "AssetManager.hpp"
#include "GameObjects.hpp"
#include "GameRenderer.hpp"
#include "Texture.hpp"
#include "game-common.hpp"
#include "std-common.hpp"

ge::Texture *ballSprite;

namespace ge {
// Initialization
void SudokuBoard::onInit() {
  // Load the border sprite sheet
  TextureSplitProperties props{};
  props.srcSizeX = 64;
  props.srcSizeY = 64;
  props.xSplitCount = 5;
  props.ySplitCount = 1;
  borderTextures = ge::Texture::CreateSheet("assets/borders.png", props);

  // Load the numbers sprite sheet
  props.srcSizeX = 32;
  props.srcSizeY = 48;
  props.xSplitCount = 10;
  props.ySplitCount = 1;
  numberTextures = ge::Texture::CreateSheet("assets/numbers.png", props);

  transform.position.x = (GameRenderer::windowWidth - 64 * 9) / 2.0f;
  transform.position.y = (GameRenderer::windowHeight - 64 * 9) / 2.0f;

  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      int randomValue = rand() % 10;
      size_t index = col + row * 9;
      placedNumbers[index] = randomValue;
    }
  }

  ge::log_msg("SudokuBoard", "Initialized!");
}

void SudokuBoard::update() {}

// Render loop
void SudokuBoard::render() {
  drawSudokuBoard();
  drawPlacedNumbers();
}

void SudokuBoard::drawSudokuBoard() {
  for (int row = -1; row < 10; row++) {
    for (int col = -1; col < 10; col++) {
      // determine the destination of the texture on the screen
      SDL_FRect tmpDst{64 * float(col) + transform.position.x,
                       64 * float(row) + transform.position.y, 64, 64};

      // offset to center

      // Draw checker
      if (col >= 0 && col < 9 && row >= 0 && row < 9)
        ge::GameRenderer::drawTexture(borderTextures[BorderTextureID::CHECKER],
                                      tmpDst);

      // Draw borders on x
      if (row >= 0 && row < 9) {
        if (col % 3 == 0)
          ge::GameRenderer::drawTexture(borderTextures[BorderTextureID::LEFT],
                                        tmpDst);
        else if ((col + 1) % 3 == 0)
          ge::GameRenderer::drawTexture(borderTextures[BorderTextureID::RIGHT],
                                        tmpDst);
      }

      // Draw borders on y
      if (col >= 0 && col < 9) {
        if (row % 3 == 0)
          ge::GameRenderer::drawTexture(borderTextures[BorderTextureID::TOP],
                                        tmpDst);
        else if ((row + 1) % 3 == 0)
          ge::GameRenderer::drawTexture(borderTextures[BorderTextureID::BOTTOM],
                                        tmpDst);
      }
    }
  }
}

void SudokuBoard::drawPlacedNumbers() {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      // determine the destination of the texture on the screen
      SDL_FRect tmpDst{64 * float(col) + transform.position.x + 16,
                       64 * float(row) + transform.position.y + 8, 32, 48};

      // get the texture id
      size_t index = col + row * 9;
      NumberTextureID texID =
          static_cast<NumberTextureID>(placedNumbers.at(index));

      // skip zero's
      if (texID == ZERO)
        continue;

      ge::GameRenderer::drawTexture(numberTextures[texID], tmpDst);
    }
  }
}

int SudokuBoard::getCell(const size_t &col, const size_t &row) {
  size_t index = col + row * 9;
  return placedNumbers.at(index);
}
void SudokuBoard::setCell(const size_t &col, const size_t &row,
                          const int &value) {
  if (value < 0 || value > 9)
    ge::log_error(
        "SudokuBoard",
        "Cannot set cell to number less than zero or larger than nine!");
  size_t index = col + row * 9;
  placedNumbers[index] = value;
}

void SudokuBoard::onClean() {}

void SudokuBoard::onDestroy() {}
} // namespace ge
