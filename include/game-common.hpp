#pragma once

// game
#include "GameEngine.hpp"
#include "GameInput.hpp"
#include "GameObject.hpp"
#include "GameRenderer.hpp"
#include "ResourceManager.hpp"
#include "Texture.hpp"
#include "vector2.hpp"

// logging
namespace ge {
inline void throw_runtime_error(const std::string &header,
                                const std::string &msg) {
  throw std::runtime_error("[" + header + "] " + msg);
}

inline void log_msg(const std::string &header, const std::string &msg) {
  std::cout << "[" << header << "] " << msg << "\n";
}
} // namespace ge

// standard texture sizes
#define TXT_STND_SIZE {0, 0, 64, 64}
