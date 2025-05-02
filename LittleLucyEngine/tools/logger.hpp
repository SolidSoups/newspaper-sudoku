#pragma once
#include <string>
#include <iostream>

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
