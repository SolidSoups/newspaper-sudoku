#include "GameInput.hpp"
#include "GameObjects.hpp"
#include "GameRenderer.hpp"
#include "ResourceManager.hpp"
#include "game-common.hpp"
#include <algorithm>
#include <string>

ge::Texture *ballSprite;

namespace ge {
// Initialization
void SudokuBoard::onInit() {
  // Load the sprite sheet
  TextureSplitProperties props{};
  props.srcSizeX = 64;
  props.srcSizeY = 64;
  props.xSplitCount = 5;
  props.ySplitCount = 1;
  borderTextures = ge::Texture::CreateSheet("assets/borders.png", props);

  transform.position.x = (GameRenderer::windowWidth - 64 * 9) / 2.0f;
  transform.position.y = (GameRenderer::windowHeight - 64 * 9) / 2.0f;

  // get the ball sprite
  // ballSprite = new Texture("assets/shinyball.png", {0, 0, 64, 64});

  // Load selected texture
  selectedTexture = Texture("assets/selected_cell.png", TXT_STND_SIZE);
}

void SudokuBoard::update() {}

bool SudokuBoard::isPosInBounds(const vector2 &pos) {
  return pos.x >= transform.position.x && pos.y >= transform.position.y &&
         pos.x < transform.position.x + 64 * 9 &&
         pos.y < transform.position.y + 64 * 9;
}

// Render loop
void SudokuBoard::render() {
  // determine if player mouse is in bounds
  vector2 mousePos = ge::GameInput::getMousePosition();
  if (isPosInBounds(mousePos)) {
    // determine the square
    int col = (mousePos.x - transform.position.x) / 64;
    int row = (mousePos.y - transform.position.y) / 64;
    SDL_FRect dst{64 * float(col) + transform.position.x,
                  64 * float(row) + transform.position.y, 64, 64};
    ResourceManager::drawTexture(selectedTexture, dst);
  }

  // Draw the backdrop of the board
  drawSudokuBoard();
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
        ResourceManager::drawTexture(borderTextures[BorderTextureID::CHECKER],
                                     tmpDst);

      // Draw borders on x
      if (row >= 0 && row < 9) {
        if (col % 3 == 0)
          ResourceManager::drawTexture(borderTextures[BorderTextureID::LEFT],
                                       tmpDst);
        else if ((col + 1) % 3 == 0)
          ResourceManager::drawTexture(borderTextures[BorderTextureID::RIGHT],
                                       tmpDst);
      }

      // Draw borders on y
      if (col >= 0 && col < 9) {
        if (row % 3 == 0)
          ResourceManager::drawTexture(borderTextures[BorderTextureID::TOP],
                                       tmpDst);
        else if ((row + 1) % 3 == 0)
          ResourceManager::drawTexture(borderTextures[BorderTextureID::BOTTOM],
                                       tmpDst);
      }
    }
  }
}

void SudokuBoard::onClean() {}

void SudokuBoard::onDestroy() {}
} // namespace ge
