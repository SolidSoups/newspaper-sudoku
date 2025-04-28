#pragma once

#include "game-common.hpp"

namespace ge {
class SudokuBoard : public GameObject {
public:
  void onInit() override;
  void update() override;
  void render() override;
  void onClean() override;
  void onDestroy() override;

private:
  // Some helper functions
  void drawSudokuBoard();
  void drawPlacedNumbers();

private:
  // Textures
  std::vector<Texture> borderTextures;
  enum BorderTextureID { CHECKER, TOP, RIGHT, BOTTOM, LEFT };

  std::vector<Texture> numberTextures;
  enum NumberTextureID {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
  };

  Texture selectedTexture;

private:
  std::array<int, 81> placedNumbers{};
  int getCell(const size_t &col, const size_t &row);
  void setCell(const size_t &col, const size_t &row, const int &value);
};
} // namespace ge
