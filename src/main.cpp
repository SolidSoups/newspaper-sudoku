#include <cstdlib>
#include <iostream>

#include "GameEngine.hpp"
#include "SDL3/SDL_timer.h"

GameEngine *game;

int main() {
  std::cout << "[Program] Started\n";

  // Setup control of frame time
  const int FPS = 120;
  const int frameDelay = 1000 / FPS;
  uint32_t frameStart;
  int frameTime;

  game = new GameEngine();
  game->init("Sudoku", 1024, 768);

  while (game->isRunning()) {
    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  game->clean();
  delete game;

  std::cout << "[Program] Ended\n";
  return EXIT_SUCCESS;
}
