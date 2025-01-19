#pragma once

#include "concepts.hpp"
#include "patchsize/neighbors.hpp"
#include "raytrix/multiview.hpp"
#include "raytrix/state.hpp"

namespace tlct1::cvt::raytrix {

namespace _ = _cvt::raytrix;

using _::State;

using Neighbors = _cvt::Neighbors_<tlct1::cfg::raytrix::Layout>;
static_assert(tlct1::cvt::concepts::CNeighbors<Neighbors>);

} // namespace tlct1::cvt::raytrix

namespace tlct1::_cvt {

template class Neighbors_<tlct1::cfg::raytrix::Layout>;

}
