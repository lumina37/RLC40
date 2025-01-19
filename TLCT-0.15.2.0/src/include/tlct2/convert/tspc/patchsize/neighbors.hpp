#pragma once

#include <array>

#include <opencv2/core.hpp>

#include "tlct2/config/tspc.hpp"
#include "tlct2/convert/concepts.hpp"
#include "tlct2/convert/helper/neighbors.hpp"

namespace tlct2::_cvt::tspc {

using Neighbors = NearNeighbors_<tlct2::cfg::tspc::Layout>;
static_assert(tlct2::cvt::concepts::CNeighbors<Neighbors>);

} // namespace tlct2::_cvt::tspc
