#pragma once

#include <functional>
#include <unordered_map>

#include "Texture.hpp"

namespace assetDefaults
{
// Defaults
void
loadDefaultTextures();

enum BorderTextureID
{
    CHECKER,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};
enum NumberTextureID
{
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

}  // namespace assetDefaults


class AssetManager
{
private:
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
        textureCache;
    static std::unordered_map<std::string, std::shared_ptr<ge::Texture>>
        geTextureCache;
    static std::unordered_map<std::string, std::shared_ptr<ge::TextureSheet>>
        geTextureSheetCache;

public:
    // Load a texture from a filepath
    static std::shared_ptr<SDL_Texture>
    loadTexture(const char *filePath);

    // Defaults
    static void
    loadDefaultTextures();

public:
    //  caches ge::Texture with the filePath as an index
    static ge::Texture *
    createCachedGETexture(
        const char *filepath, const ge::TextureProperties &props);
    // Retrieves a cached ge::Texture with the filePath as an index
    static ge::Texture *
    retrieveGETextureCache(const char *filePath);

    // caches ge::TextureSheet with the filePath as an index
    static ge::TextureSheet *
    createCachedGETextureSheet(
        const char *filepath, const ge::TextureSplitProperties &props);
    // Retrieves a cached ge::TextureSheet with the filePath as an index
    static ge::TextureSheet *
    retrieveGETextureSheetCache(const char *filePath);

public:
};
