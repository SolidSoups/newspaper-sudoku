#include "llengine.hpp"

#include "GameObject.hpp"
#include "UIToolbar.hpp"
#include "SudokuBoard.hpp"
#include "AssetManager.hpp"
#include "GameInput.hpp"
#include "logger.hpp"
#include <vector>

UIToolbar *uiToolbar;
SudokuBoard *board;
std::vector<UIToolbarNumber *> numberSelections;

void
LittleLucyEngine::internal_init()
{
    // Load textures
    assetDefaults::loadDefaultTextures();

    // add a event handler for the key down press,  TODO: encapsulate
    keyDownHandler = [this](const SDL_Event &e)
    {
        onKeyDown(e);
    };
    ge::GameInput::registerKeyDownCallback(keyDownHandler);

    // Add some default gameObjects
    uiToolbar = addGameObject<UIToolbar>();
    board = addGameObject<SudokuBoard>();
}
void
LittleLucyEngine::internal_handleEvents(const SDL_Event &e)
{
}
void
LittleLucyEngine::internal_update_early(const float &deltaTime)
{
}
void
LittleLucyEngine::internal_update_late(const float &deltaTime)
{
    // TODO: Clean up
    if (numberSelections.size() != 0)
    {
        for (auto it = numberSelections.begin(); it != numberSelections.end();)
        {
            if ((*it)->isDestroyed())
            {
                (*it)->doClean();
                delete (*it);
                it = numberSelections.erase(it);
            }
            else
            {
                (*it)->update(deltaTime);
                ++it;
            }
        }
    }
}
void
LittleLucyEngine::internal_render()
{
    // TODO: Clean up
    for (auto it = numberSelections.begin(); it != numberSelections.end();)
    {
        if (!(*it)->isDestroyed())
        {
            (*it)->render();
        }
        ++it;
    }
}
void
LittleLucyEngine::internal_clean()
{
    // TODO: clean up handling events
    ge::GameInput::unregisterKeyDownCallback(keyDownHandler);
}

// Input listener
void
LittleLucyEngine::onKeyDown(const SDL_Event &e)
{
    // Get texture id from key
    uint32_t key = e.key.key;
    int texID = key - 48;
    if (texID == 0 || texID > 9)
        ge::throw_runtime_error("GameEngine", "TexID out of bounds");
    ge::log_msg(
        "GameEngine", "Spawning ui for number " + std::to_string(texID));

    // testing destroying if overlap
    for (auto it = numberSelections.begin(); it != numberSelections.end();)
    {
        if ((*it)->getTextureID() == texID)
        {
            (*it)->doDestroy();
            delete (*it);
            it = numberSelections.erase(it);
            break;
        }
        ++it;
    }

    // spawn a ui
    UIToolbarNumber *newSel = new UIToolbarNumber();
    newSel->doInit();
    newSel->setTextureID(texID);
    newSel->transform.position = {
        0,  // setting the height to match the backdrop
        uiToolbar->transform.position.y + (texID - 1) * 64
    };
    numberSelections.push_back(newSel);
}
