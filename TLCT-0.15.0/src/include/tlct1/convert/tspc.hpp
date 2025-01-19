#pragma once

#include "tlct1/convert/concepts.hpp"
#include "tlct1/convert/patchsize/neighbors.hpp"
#include "tlct1/convert/tspc/multiview.hpp"
#include "tlct1/convert/tspc/state.hpp"

namespace tlct1::cvt::tspc {

namespace _ = _cvt::tspc;

using _::State;

using Neighbors = _cvt::Neighbors_<tlct1::cfg::tspc::Layout>;
static_assert(tlct1::cvt::concepts::CNeighbors<Neighbors>);

} // namespace tlct1::cvt::tspc

namespace tlct1::_cvt {

template class Neighbors_<tlct1::cfg::tspc::Layout>;

}
