#pragma once

#include <algorithm>

namespace tlct1::_hp {

template <size_t size>
class cestring
{
public:
    constexpr cestring(const char (&str)[size]) noexcept { std::copy(str, str + size, string); }

    char string[size];
};

} // namespace tlct1::_hp
