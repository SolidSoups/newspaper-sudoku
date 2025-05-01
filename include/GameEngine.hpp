#pragma once

// Forward declare
struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;
#include "functional"

// Game Engine class
class GameEngine
{
public:
    GameEngine();
    virtual ~GameEngine();

public:
    // Game Engine Essentials
    void
    init(const char *windowTitle, int width, int height);
    void
    handleEvents();
    void
    update(const float &deltaTime);
    void
    render();
    void
    clean();

private:
    // Game Engine Essentials
    bool bIsRunning = false;
    bool bIsClean = false;

private:
    // tmps
    std::function<void(const SDL_Event &)> keyDownHandler;
    void
    onKeyDown(const SDL_Event &e);

public:
    bool
    isRunning();

private:
    SDL_Window *window;
};
