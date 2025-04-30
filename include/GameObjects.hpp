#pragma once

#include "GameObject.hpp"
#include "Texture.hpp"
#include "game-common.hpp"

namespace ge {
class SudokuBoard : public GameObject {
public:
  void onInit() override;
  void update(const float &deltaTime) override;
  void render() override;
  void onClean() override;
  void onDestroy() override;

private:
  // Some helper functions
  void drawSudokuBoard();
  void drawPlacedNumbers();

private:
  // Textures
  ge::TextureSheet *borderTextures;

  ge::TextureSheet *numberTextures;

  Texture selectedTexture;

private:
  std::array<int, 81> placedNumbers{};
  int getCell(const size_t &col, const size_t &row);
  void setCell(const size_t &col, const size_t &row, const int &value);
};

class UIToolbar : public GameObject {
public:
  void onInit() override;
  void update(const float &deltaTime) override;
  void render() override;
  void onClean() override;
  void onDestroy() override;

private:
  void drawToolbar();

private:
  // Textures
  ge::Texture *uiToolbarBackdropTexture;
  ge::TextureSheet *miniNumbersTextureSheet;
};

class UIToolbarNumberSelection : public GameObject {
public:
  UIToolbarNumberSelection() = default;

public:
  void onInit() override;
  void update(const float &deltaTime) override;
  void render() override;
  void onClean() override;
  void onDestroy() override;

public:
  inline void setTextureID(int _textureID) { textureID = _textureID; }

private:
  void drawAnimation();

private:
  // Statemachine stuff
  const float MAX_TIME = 0.5f;
  const float SIZE_RATIO_TO = 1.3;
  float accumulator = 0.0f;

private:
  ge::Texture *redNumberPlateTexture;
  ge::TextureSheet *miniNumbersTextureSheet;
  int textureID;
};
} // namespace ge
