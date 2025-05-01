#pragma once

// game
#include <functional>

#include "AssetManager.hpp"
#include "GameEngine.hpp"
#include "GameInput.hpp"
#include "GameObject.hpp"
#include "GameRenderer.hpp"
#include "Texture.hpp"
#include "vector2.hpp"

// logging
namespace ge
{
inline void
throw_runtime_error(const std::string &header, const std::string &msg)
{
    throw std::runtime_error("[" + header + "] " + msg);
}

inline void
log_msg(const std::string &header, const std::string &msg)
{
    std::cout << "[" << header << "] " << msg << "\n";
}

inline void
log_error(const std::string &header, const std::string &msg)
{
    std::cerr << "[" << header << "]" << msg << "\n";
}
}  // namespace ge

// standard texture sizes
#define TXT_STND_SIZE { 0, 0, 64, 64 }

// templated functions to help with adding callbacks
namespace callbacks
{
template <typename T>
struct function_traits;

template <typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>>
{
    using function_type = Ret(Args...);
    using pointer_type = Ret (*)(Args...);
};

template <typename Callback>
bool
functionEquals(const Callback &a, const Callback &b)
{
    using FuncPtr = typename function_traits<Callback>::pointer_type;
    return a.template target<FuncPtr>() == b.template target<FuncPtr>();
}

template <typename Callback>
void
registerCallback(std::vector<Callback> &container, Callback callback)
{
    for (const auto &cb : container)
    {
        if (functionEquals(cb, callback))
            return;
    }
    container.push_back(callback);
}

template <typename Callback>
void
unregisterCallback(std::vector<Callback> &container, Callback callback)
{
    for (auto it = container.begin(); it != container.end();)
    {
        if (functionEquals(*it, callback))
        {
            container.erase(it);
            break;
        }
        else
        {
            ++it;
        }
    }
}
}  // namespace callbacks
