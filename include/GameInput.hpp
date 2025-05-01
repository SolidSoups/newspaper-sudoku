#pragma once
#include <functional>

#include "SDL3/SDL_events.h"
#include "std-common.hpp"
#include "vector2.hpp"

namespace ge
{
class GameInput
{
private:
    static vector2 mousePosition;
    static uint32_t mouseFlags;

    static std::vector<std::function<void(SDL_Event&)>> keyDownCallbacks;
    static std::vector<std::function<void(SDL_Event&)>> keyUpCallbacks;

private:
    static void invokeKeyDown(SDL_Event& e);
    static void invokeKeyUp(SDL_Event& e);

public:
    static void
    
    poll(SDL_Event& e);

public:
    static vector2
    getMousePosition();
    static uint32_t
    getMouseFlags();

public:
    static void
    registerKeyDownCallback(std::function<void(SDL_Event&)> callback);
    static void
    unregisterKeyDownCallback(std::function<void(SDL_Event&)> callback);
    static void
    registerKeyUpCallback(std::function<void(SDL_Event&)> callback);
    static void
    unregisterKeyUpCallback(std::function<void(SDL_Event&)> callback);
};
}  // namespace ge
