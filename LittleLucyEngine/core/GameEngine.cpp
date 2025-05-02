#include "core/GameEngine.hpp"

#include "../sdl-common.hpp"
#include "core/GameInput.hpp"
#include "core/GameRenderer.hpp"
#include "tools/logger.hpp"
#include "gameObject/GameObject.hpp"

// Constructor
GameEngine::GameEngine()
{
}
// Destructor
GameEngine::~GameEngine()
{
    if (!bIsClean)
        clean();
}

// Base initialization of game engine
void
GameEngine::init(const char* windowTitle, int width, int height)
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
    // Set window size so everyone can access it
    ge::GameRenderer::windowWidth = width;
    ge::GameRenderer::windowHeight = height;

    // Set state flags
    bIsRunning = true;
    bIsClean = false;

    // pass to subclasses
    internal_init();

    ge::log_msg("GameEngine", "Initialized!");
}

// Base handling of events
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

    // pass to subclasses
    internal_handleEvents(event);
}

void
GameEngine::update(const float& deltaTime)
{
    // pass to subclass first
    internal_update_early(deltaTime);

    // check if we need to initialize any new game objects
    if (!newGameObjects.empty())
    {
        for (auto go : newGameObjects)
        {
            go->doInit();
            activeGameObjects.push_back(go);
        }
        newGameObjects.clear();
    }

    // update or delete gameObjects
    if (!activeGameObjects.empty())
    {
        for (auto it = activeGameObjects.begin();
            it != activeGameObjects.end();)
        {
            if ((*it)->isDestroyed())
            {
                (*it)->doClean();
                delete (*it);
                it = activeGameObjects.erase(it);
            }
            else
            {
                (*it)->update(deltaTime);
                ++it;
            }
        }
    }

    // pass to subclass after
    internal_update_late(deltaTime);
}

void
GameEngine::render()
{
    // Core render loop
    SDL_RenderClear(ge::GameRenderer::renderer);

    for (auto gameObject : activeGameObjects)
    {
        if (!gameObject->isDestroyed())
            gameObject->render();
    }

    // Pass to subclass
    internal_render();

    SDL_RenderPresent(ge::GameRenderer::renderer);
}

void
GameEngine::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(ge::GameRenderer::renderer);
    SDL_Quit();

    for (auto it = activeGameObjects.begin(); it != activeGameObjects.end();)
    {
        (*it)->doClean();
        delete *it;
        it = activeGameObjects.erase(it);
    }
    internal_clean();

    bIsClean = true;
    ge::log_msg("GameEngine", "Cleaned!");
}

// runs the core loop of the game engine
void
GameEngine::run(const float& deltaTime)
{
    handleEvents();
    update(deltaTime);
    render();
}

bool
GameEngine::isRunning()
{
    return bIsRunning;
}
