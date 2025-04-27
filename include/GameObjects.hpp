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
  bool isPosInBounds(const vector2& pos);

private:
  // Textures
  std::vector<Texture> borderTextures;
  enum BorderTextureID { CHECKER, TOP, RIGHT, BOTTOM, LEFT };

  Texture selectedTexture;

private:
  float posX, posY;
};
} // namespace ge
