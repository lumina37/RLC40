#pragma once

#include <concepts>

namespace tlct1::_cfg::concepts {

template <typename Tf, typename Tv>
concept is_factory_of = requires(Tf factory) {
    { factory() } -> std::same_as<Tv>;
};

} // namespace tlct1::_cfg::concepts
