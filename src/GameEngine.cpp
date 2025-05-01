#include "GameEngine.hpp"

#include "AssetManager.hpp"
#include "GameInput.hpp"
#include "GameObjects.hpp"
#include "GameRenderer.hpp"
#include "game-common.hpp"
#include "sdl-common.hpp"

ge::SudokuBoard board;
ge::UIToolbar uiToolbar;
std::vector<ge::UIToolbarNumber *> numberSelections;

GameEngine::GameEngine()
{
}
GameEngine::~GameEngine()
{
    if (!bIsClean)
    {
        clean();
    }
}

// GAME ENGINE ESSENTIALS
void
GameEngine::init(const char *windowTitle, int width, int height)
{
    // Initialize sdl
    if (!SDL_Init(SDL_INIT_VIDEO))
        ge::throw_runtime_error("GameEngine", "Failed to init SDL!");

    // Initialize window
    SDL_WindowFlags flags = 0;
    window = SDL_CreateWindow(windowTitle, width, height, flags);
    if (!window)
        ge::throw_runtime_error("GameEngine", "Failed to init SDL Window!");

    // Initialize renderer
    ge::GameRenderer::renderer = SDL_CreateRenderer(window, nullptr);
    if (!ge::GameRenderer::renderer)
        ge::throw_runtime_error("GameEngine", "Failed to init SDL Renderer!");
    SDL_SetRenderDrawColor(ge::GameRenderer::renderer, 220, 220, 220, 255);

    ge::GameRenderer::windowWidth = width;
    ge::GameRenderer::windowHeight = height;

    assetDefaults::loadDefaultTextures();

    keyDownHandler = [this](const SDL_Event &e)
    {
        onKeyDown(e);
    };
    ge::GameInput::registerKeyDownCallback(keyDownHandler);

    board.doInit();
    uiToolbar.doInit();

    // Set flags
    bIsRunning = true;
    bIsClean = false;

    ge::log_msg("GameEngine", "Initialized!");
}

void
GameEngine::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    ge::GameInput::poll(event);
    switch (event.type)
    {
        case SDL_EVENT_QUIT:
            bIsRunning = false;
            break;
        default:
            break;
    }
}

void
GameEngine::update(const float &deltaTime)
{
    board.update(deltaTime);
    uiToolbar.update(deltaTime);

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
GameEngine::render()
{
    // Core render loop
    SDL_RenderClear(ge::GameRenderer::renderer);

    board.render();
    uiToolbar.render();
    for (auto it = numberSelections.begin(); it != numberSelections.end();)
    {
        if (!(*it)->isDestroyed())
        {
            (*it)->render();
        }
        ++it;
    }

    SDL_RenderPresent(ge::GameRenderer::renderer);
}

void
GameEngine::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(ge::GameRenderer::renderer);
    SDL_Quit();

    // clean up events
    ge::GameInput::unregisterKeyDownCallback(keyDownHandler);

    bIsClean = true;
    ge::log_msg("GameEngine", "Cleaned!");
}

void
GameEngine::onKeyDown(const SDL_Event &e)
{
    int texID;
    // determine textureID
    switch (e.key.key)
    {
        case SDLK_1:
            texID = 1;
            break;
        case SDLK_2:
            texID = 2;
            break;
        case SDLK_3:
            texID = 3;
            break;
        case SDLK_4:
            texID = 4;
            break;
        case SDLK_5:
            texID = 5;
            break;
        case SDLK_6:
            texID = 6;
            break;
        case SDLK_7:
            texID = 7;
            break;
        case SDLK_8:
            texID = 8;
            break;
        case SDLK_9:
            texID = 9;
            break;
        default:
            return;
    }
    ge::log_msg(
        "GameEngine", "Spawning ui for number " + std::to_string(texID));

    // testing returning if overlap
    // if (std::any_of(numberSelections.begin(),
    //         numberSelections.end(),
    //         [texID](ge::UIToolbarNumber *ui)
    //         {
    //             return ui->getTextureID() == texID;
    //         }))
    // {
    //     ge::log_msg("GameEngine", "UI Number is already active");
    //     return;
    // }

    // testing destroying if overlap
    for(auto it = numberSelections.begin(); it != numberSelections.end();){
        if((*it)->getTextureID() == texID){
            (*it)->doDestroy();
            delete (*it);
            it = numberSelections.erase(it);
            break;
        }
        ++it;
    }

    // spawn a ui
    ge::UIToolbarNumber *newSel = new ge::UIToolbarNumber();
    newSel->doInit();
    newSel->setTextureID(texID);
    newSel->transform.position = { 0,
        uiToolbar.transform.position.y + (texID - 1) * 64 };
    numberSelections.push_back(newSel);
}

bool
GameEngine::isRunning()
{
    return bIsRunning;
}
