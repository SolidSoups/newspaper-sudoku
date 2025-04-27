cmake_minimum_required(VERSION 3.16)
project(Sudoku LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")

# Tell SDL not to use OpenGL ES
set(SDL_OPENGLES OFF CACHE BOOL "Disable OpenGL ES support")
set(SDL_RENDER_D3D OFF CACHE BOOL "Disable Direct3D render backend")

# Add SDL and NetCommon
add_subdirectory(libs/SDL EXCLUDE_FROM_ALL)
add_subdirectory(libs/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(libs/NetCommon)

# Collect source files
set(SOURCES
    src/main.cpp
    src/GameEngine.cpp
    src/ResourceManager.cpp
    src/Texture.cpp
    src/SudokuBoard.cpp
    src/GameRenderer.cpp
    src/GameInput.cpp
)

# Collect header files (this makes clangd and IDEs happy)
set(HEADERS
    include/sdl-common.hpp
    include/std-common.hpp
    include/game-common.hpp
    include/GameEngine.hpp
    include/GameRenderer.hpp
    include/GameInput.hpp
    include/GameObject.hpp
    include/GameObjects.hpp
    include/ResourceManager.hpp
    include/Texture.hpp
    include/ECS.hpp
    include/Components.hpp
    include/vector2.hpp
)

# Create the executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

# Compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)

# Add error reporting flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -fdiagnostics-color=always)
endif()

# Include directories
target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/SDL/include
    ${CMAKE_SOURCE_DIR}/libs/SDL_image/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    SDL3::SDL3
    SDL3_image::SDL3_image
    NetCommon
)
