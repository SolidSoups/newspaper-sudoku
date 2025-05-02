#include "core/AssetManager.hpp"

#include <unordered_map>

#include "../../../include/game-common.hpp"
#include "../../SDL/include/SDL3/SDL_render.h"
#include "core/GameRenderer.hpp"
#include "tools/logger.hpp"
#include "renderer/Texture.hpp"

void
assetDefaults::loadDefaultTextures()
{
    // Load the border sprite sheet
    ge::TextureSplitProperties props{};
    props.srcSizeX = 64;
    props.srcSizeY = 64;
    props.xSplitCount = 5;
    props.ySplitCount = 1;
    AssetManager::createCachedGETextureSheet("assets/borders.png", props);

    // Load the numbers sprite sheet
    props.srcSizeX = 32;
    props.srcSizeY = 48;
    props.xSplitCount = 10;
    props.ySplitCount = 1;
    AssetManager::createCachedGETextureSheet("assets/numbers.png", props);

    // Load the mini numbers sprite sheet
    props.srcSizeX = 20;
    props.srcSizeY = 32;
    props.xSplitCount = 10;
    props.ySplitCount = 1;
    AssetManager::createCachedGETextureSheet("assets/mini-numbers.png", props);

    // Load the number toolbar ui backdrop
    props.srcSizeX = 64;
    props.srcSizeY = 640;
    AssetManager::createCachedGETexture(
        "assets/numbers_toolbar_ui_backdrop.png", props);

    // Load the number toolbar ui backdrop
    props.srcSizeX = 64;
    props.srcSizeY = 64;
    AssetManager::createCachedGETexture("assets/red_number_plate.png", props);
}

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>
    AssetManager::textureCache{};
std::unordered_map<std::string, std::shared_ptr<ge::Texture>>
    AssetManager::geTextureCache;
std::unordered_map<std::string, std::shared_ptr<ge::TextureSheet>>
    AssetManager::geTextureSheetCache;

std::shared_ptr<SDL_Texture>
AssetManager::loadTexture(const char *filePath)
{
    // retrieve cache if available
    if (textureCache.find(filePath) != textureCache.end())
    {
        return textureCache[filePath];
    }

    // otherwise create texture and cache it
    SDL_Surface *tmpSurface = IMG_Load(filePath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(
        ge::GameRenderer::renderer, tmpSurface);
    SDL_DestroySurface(tmpSurface);

    // cache
    std::shared_ptr<SDL_Texture> ptr(texture, SDL_DestroyTexture);
    textureCache[filePath] = ptr;

    return ptr;
}

// Load the default textures in the world so that they get cached

ge::Texture *
AssetManager::createCachedGETexture(
    const char *filePath, const ge::TextureProperties &props)
{
    ge::log_msg("AssetManager",
        "Creating cached ge::Texture '" + std::string(filePath) + "'");
    ge::Texture *newTex = new ge::Texture(filePath, props);
    std::shared_ptr<ge::Texture> ptr(newTex);
    geTextureCache[filePath] = ptr;
    return ptr.get();
}

ge::Texture *
AssetManager::retrieveGETextureCache(const char *filePath)
{
    if (geTextureCache.find(filePath) == geTextureCache.end())
        ge::throw_runtime_error("AssetManager",
            "Could not find texture '" + std::string(filePath) + "' in cache!");
    return geTextureCache.at(filePath).get();
}

ge::TextureSheet *
AssetManager::createCachedGETextureSheet(
    const char *filePath, const ge::TextureSplitProperties &props)
{
    ge::log_msg("AssetManager",
        "Creating cached ge::TextureSheet '" + std::string(filePath) + "'");
    ge::TextureSheet *newTexSheet = new ge::TextureSheet(filePath, props);
    std::shared_ptr<ge::TextureSheet> ptr(newTexSheet);
    geTextureSheetCache[filePath] = ptr;
    return ptr.get();
}

ge::TextureSheet *
AssetManager::retrieveGETextureSheetCache(const char *filePath)
{
    if (geTextureSheetCache.find(filePath) == geTextureSheetCache.end())
        ge::throw_runtime_error("AssetManager",
            "Could not find the texture sheet '" + std::string(filePath) +
                "' in cache!");
    return geTextureSheetCache.at(filePath).get();
}
