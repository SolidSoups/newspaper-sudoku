#pragma once

// Forward declare
struct SDL_Window;
struct SDL_Renderer;

// Game Engine class
class GameEngine {
public:
  GameEngine();
  virtual ~GameEngine();

public:
  // Game Engine Essentials
  void init(const char *windowTitle, int width, int height);
  void handleEvents();
  void update();
  void render();
  void clean();

private:
  // Game Engine Essentials
  bool bIsRunning = false;
  bool bIsClean = false;

public:
  bool isRunning();

private:
  SDL_Window *window;
};
