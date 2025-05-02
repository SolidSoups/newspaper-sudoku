#pragma once
#include "gameObject/GameObject.hpp"

namespace ge {
    struct TextureSheet;
}


class SudokuBoard : public GameObject
{
public:
    void
    onInit() override;
    void
    update(const float &deltaTime) override;
    void
    render() override;
    void
    onClean() override;
    void
    onDestroy() override;

private:
    // Some helper functions
    void
    drawSudokuBoard();
    void
    drawPlacedNumbers();

private:
    // Textures
    ge::TextureSheet *borderTextures;
    ge::TextureSheet *numberTextures;

private:
    std::array<int, 81> placedNumbers{};
    int
    getCell(const size_t &col, const size_t &row);
    void
    setCell(const size_t &col, const size_t &row, const int &value);
};
