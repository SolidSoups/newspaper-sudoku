#include <cstdlib>
#include <iostream>

#include "tools/logger.hpp"
#include "core/GameEngine.hpp"
#include "include/game-common.hpp"
#include "sdl-common.hpp"
#include "llengine.hpp"

GameEngine *game;

int
main()
{
    ge::log_msg("Program", "Started!");

    // Setup control of frame time
    const int FPS = 120;
    const int frameDelay = 1000 / FPS;
    uint32_t frameStart;
    int frameTime;

    game = new LittleLucyEngine();
    game->init("Sudoku", 1024, 768);

    ge::log_msg("Program", "Starting game loop");
    while (game->isRunning())
    {
        frameStart = SDL_GetTicks();

        game->run(frameDelay / 1000.0f);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
    delete game;

    ge::log_msg("Program", "Ended!");
    return EXIT_SUCCESS;
}
