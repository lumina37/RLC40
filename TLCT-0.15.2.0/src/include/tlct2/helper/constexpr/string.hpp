#pragma once

#include <algorithm>
#include <cstddef>

namespace tlct2::_hp {

template <size_t N>
class cestring
{
public:
    consteval inline cestring(const char (&str)[N]) noexcept { std::copy(str, str + N, string); }

    char string[N]{};
};

} // namespace tlct2::_hp
