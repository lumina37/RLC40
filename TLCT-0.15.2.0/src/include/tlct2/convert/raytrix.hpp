#pragma once

#include "tlct2/convert/concepts.hpp"
#include "tlct2/convert/raytrix/multiview.hpp"
#include "tlct2/convert/raytrix/patchsize.hpp"
#include "tlct2/convert/raytrix/state.hpp"

namespace tlct2::cvt::raytrix {

namespace _ = _cvt::raytrix;

using _::FarNeighbors;
using _::NearNeighbors;
using _::State;

static_assert(tlct2::cvt::concepts::CNeighbors<NearNeighbors>);

} // namespace tlct2::cvt::raytrix
