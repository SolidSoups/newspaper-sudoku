#pragma once

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
