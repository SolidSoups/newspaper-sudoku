#include "core/GameInput.hpp"
#include "core/callbacks.hpp"

// std
#include <vector>
#include <functional>

#include "../sdl-common.hpp"
#include "tools/vector2.hpp"

// Static members
vector2 ge::GameInput::mousePosition = {};
uint32_t ge::GameInput::mouseFlags;
std::vector<std::function<void(SDL_Event&)>> ge::GameInput::keyDownCallbacks{};
std::vector<std::function<void(SDL_Event&)>> ge::GameInput::keyUpCallbacks{};
bool ge::GameInput::bIsKeyDown = false;

void
ge::GameInput::poll(SDL_Event& e)
{
    mouseFlags = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    switch (e.type)
    {
        case SDL_EVENT_KEY_DOWN:
            invokeKeyDown(e);
            break;
        case SDL_EVENT_KEY_UP:
            invokeKeyUp(e);
            break;
    }
}

void
ge::GameInput::invokeKeyDown(SDL_Event& e)
{
    if (bIsKeyDown)
        return;
    bIsKeyDown = true;
    for (auto& func : keyDownCallbacks)
        func(e);
}
void
ge::GameInput::invokeKeyUp(SDL_Event& e)
{
    if (!bIsKeyDown)
        return;
    bIsKeyDown = false;
    for (auto& func : keyUpCallbacks)
        func(e);
}

// getters
vector2
ge::GameInput::getMousePosition()
{
    return mousePosition;
}
uint32_t
ge::GameInput::getMouseFlags()
{
    return mouseFlags;
}

// register events
void
ge::GameInput::registerKeyDownCallback(std::function<void(SDL_Event&)> callback)
{
    callbacks::registerCallback(keyDownCallbacks, callback);
}
void
ge::GameInput::unregisterKeyDownCallback(
    std::function<void(SDL_Event&)> callback)
{
    callbacks::unregisterCallback(keyDownCallbacks, callback);
}
void
ge::GameInput::registerKeyUpCallback(std::function<void(SDL_Event&)> callback)
{
    callbacks::registerCallback(keyUpCallbacks, callback);
}
void
ge::GameInput::unregisterKeyUpCallback(std::function<void(SDL_Event&)> callback)
{
    callbacks::unregisterCallback(keyDownCallbacks, callback);
}
