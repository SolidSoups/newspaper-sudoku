cmake_minimum_required(VERSION 3.16)

project(LLEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(LLEngine
        core/renderer/Texture.hpp
        core/renderer/Texture.cpp
        core/GameEngine.hpp
        core/GameEngine.cpp
        core/GameInput.cpp
        core/AssetManager.hpp
        core/AssetManager.cpp
        core/GameRenderer.hpp
        core/GameRenderer.cpp
        core/callbacks.hpp

        gameObject/ECS.hpp
        gameObject/Components.hpp
        gameObject/GameObject.hpp

        tools/logger.hpp
        tools/vector2.hpp

        sdl-common.hpp
)

target_include_directories(LLEngine
        PUBLIC
        .
        core
        core/renderer
        gameObject
        tools
)

target_link_libraries(LLEngine
    PUBLIC
        SDL3::SDL3
        SDL3_image::SDL3_image
)
