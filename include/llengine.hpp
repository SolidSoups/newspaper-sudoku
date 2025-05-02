#pragma once
#include "core/GameEngine.hpp"

class LittleLucyEngine : public GameEngine
{
public:
    void
    internal_init() override;
    void
    internal_handleEvents(const SDL_Event& e) override;
    void
    internal_update_early(const float& deltaTime) override;
    void
    internal_update_late(const float& deltaTime) override;
    void
    internal_render() override;
    void
    internal_clean() override;
private:
    // tmp
    std::function<void(const SDL_Event &)> keyDownHandler;
    
    void
    onKeyDown(const SDL_Event &e);

public:
};