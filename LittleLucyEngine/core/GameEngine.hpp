#pragma once
#include <functional>

#include "../../../include/game-common.hpp"
#include "tools/logger.hpp"
#include "gameObject/GameObject.hpp"

// Forward declare
struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

// Game Engine class
class GameEngine
{
public:
    GameEngine();
    virtual ~GameEngine();

public:
    // Public initialization of the GameEngine, will initialize SDL, Renderer
    // and Input management.
    void
    init(const char* windowTitle, int width, int height);
    // Public handling of SDL window events, such as mouse or keyboard
    // interaction.
    void
    handleEvents();
    // Public update loop of the GameEngine.
    void
    update(const float& deltaTime);
    // Public render loop of the GameEngine.
    void
    render();
    // Public cleaning function for the GameEngine.
    void
    clean();

public:
    // Called after the GameEngine initializes.
    virtual void
    internal_init() = 0;
    // Called after the GameEngine fetches and handles events.
    virtual void
    internal_handleEvents(const SDL_Event& e) = 0;
    // Called before the GameEngine's update loop, before initialization of
    // gameObjects.
    virtual void
    internal_update_early(const float& deltaTime) = 0;
    // Called after the GameEngine's update loop, after initialization of
    // gameObjects.
    virtual void
    internal_update_late(const float& deltaTime) = 0;
    // Called during the GameEngine's render loop and is ready to receive draw
    // calls.
    virtual void
    internal_render() = 0;
    // Called after the GameEngine has cleaned up.
    virtual void
    internal_clean() = 0;

public:
    // Runs the core loop of the GameEngine.
    void
    run(const float& deltaTime);

private:
    // Flag to track if the GameEngine is running.
    bool bIsRunning = false;
    // Flag to track if the GameEngine is clean.
    bool bIsClean = false;

private:
public:
    // Checks if the GameEngine is still running.
    bool
    isRunning();

private:
    // A pointer to the SDL_Window this GameEngine has created.
    SDL_Window* window;

private:
    // Container for GameObjects which need to be initialized.
    std::vector<GameObject*> activeGameObjects;
    // Container for the active GameObjects, which includes GameObjects
    // which have been destroyed and are about to be cleaned.
    std::vector<GameObject*> newGameObjects;

public:
    // Adds a new GameObject to the system. The GameObject will be put in the
    // initialization collection.
    template <typename T, typename... Args>
    T*
    addGameObject(Args&&... args)
    {
        // Construct object
        T* gameObject = new T(std::forward<Args>(args)...);

        // check if gameObject is already being added
        if (std::any_of(newGameObjects.begin(),
                newGameObjects.end(),
                [gameObject](GameObject* other)
                {
                    return other->getID() == gameObject->getID();
                }))
        {
            ge::log_error("GameObject",
                "GameEngine::addGameObject(..) -> GameObject is already queued "
                "for "
                "initialization.");
            return nullptr;
        }

        // check if gameObject is already active
        if (std::any_of(activeGameObjects.begin(),
                activeGameObjects.end(),
                [gameObject](GameObject* other)
                {
                    return other->getID() == gameObject->getID();
                }))
        {
            ge::log_error("GameObject",
                "GameEngine::addGameObject(..) -> GameObject is already "
                "active.");
            return nullptr;
        }

        newGameObjects.push_back(gameObject);
        return gameObject;
    }
};
