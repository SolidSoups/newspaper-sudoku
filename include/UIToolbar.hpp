#pragma once

#include "gameObject/GameObject.hpp"

// Forward declaration
namespace ge
{
struct Texture;
struct TextureSheet;
}  // namespace ge

// This class acts as a toolbar and handles user toolbar interactions
class UIToolbar : public GameObject
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
    void
    drawToolbar();

private:
    // Textures
    ge::Texture *uiToolbarBackdropTexture;
    ge::TextureSheet *miniNumbersTextureSheet;
};

// Simple gameObject for quick animation on toolbar
class UIToolbarNumber : public GameObject
{
public:
    UIToolbarNumber() = default;

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

public:
    inline void
    setTextureID(int _textureID)
    {
        textureID = _textureID;
    }

    inline int
    getTextureID() const
    {
        return textureID;
    }

private:
    void
    drawAnimation();

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
