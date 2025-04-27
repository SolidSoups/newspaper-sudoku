#include "GameInput.hpp"
#include "SDL3/SDL_mouse.h"
#include "sdl-common.hpp"
#include "vector2.hpp"

vector2 ge::GameInput::mousePosition = {};
uint32_t ge::GameInput::mouseFlags;

void ge::GameInput::poll() {
  mouseFlags = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
}

// getters
vector2 ge::GameInput::getMousePosition() { return mousePosition; } 
uint32_t ge::GameInput::getMouseFlags() { return mouseFlags; }
