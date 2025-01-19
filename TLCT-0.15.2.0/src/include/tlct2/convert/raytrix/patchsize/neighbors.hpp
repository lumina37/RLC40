#pragma once

#include <array>

#include <opencv2/core.hpp>

#include "tlct2/config/raytrix.hpp"
#include "tlct2/convert/concepts.hpp"
#include "tlct2/convert/helper/neighbors.hpp"

namespace tlct2::_cvt::raytrix {

using NearNeighbors = NearNeighbors_<tlct2::cfg::raytrix::Layout>;
static_assert(tlct2::cvt::concepts::CNeighbors<NearNeighbors>);

using FarNeighbors = FarNeighbors_<tlct2::cfg::raytrix::Layout>;
static_assert(tlct2::cvt::concepts::CNeighbors<FarNeighbors>);

} // namespace tlct2::_cvt::raytrix
