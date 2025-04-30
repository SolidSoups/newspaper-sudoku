#include "GameEngine.hpp"

#include "AssetManager.hpp"
#include "GameInput.hpp"
#include "GameObjects.hpp"
#include "GameRenderer.hpp"
#include "game-common.hpp"
#include "sdl-common.hpp"

ge::SudokuBoard board;
ge::UIToolbar uiToolbar;
ge::UIToolbarNumberSelection *numberSelection;
bool isSpawned = false;

GameEngine::GameEngine() {}
GameEngine::~GameEngine() {
  if (!bIsClean) {
    clean();
  }
}

// GAME ENGINE ESSENTIALS
void GameEngine::init(const char *windowTitle, int width, int height) {
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

  board.doInit();
  uiToolbar.doInit();

  // Set flags
  bIsRunning = true;
  bIsClean = false;

  ge::log_msg("GameEngine", "Initialized!");
}

void GameEngine::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  ge::GameInput::poll();
  switch (event.type) {
  case SDL_EVENT_QUIT:
    bIsRunning = false;
    break;
  default:
    break;
  }
}

void GameEngine::update(const float &deltaTime) {
  board.update(deltaTime);
  uiToolbar.update(deltaTime);

  vector2 mousePos = ge::GameInput::getMousePosition();
  if (!isSpawned && mousePos.x > 400) {
    isSpawned = true;
    numberSelection = new ge::UIToolbarNumberSelection();
    numberSelection->doInit();
    numberSelection->setTextureID(2);
    numberSelection->transform.position = {0,
                                           uiToolbar.transform.position.y + 64};
  }

  if (isSpawned && numberSelection->isDestroyed()) {
    isSpawned = false;
    delete numberSelection;
  }
  if (isSpawned)
    numberSelection->update(deltaTime);
}

void GameEngine::render() {
  // Core render loop
  SDL_RenderClear(ge::GameRenderer::renderer);

  board.render();
  uiToolbar.render();
  if (isSpawned)
    numberSelection->render();

  SDL_RenderPresent(ge::GameRenderer::renderer);
}

void GameEngine::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(ge::GameRenderer::renderer);
  SDL_Quit();

  bIsClean = true;
  ge::log_msg("GameEngine", "Cleaned!");
}

bool GameEngine::isRunning() { return bIsRunning; }
