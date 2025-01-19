#pragma once

#include "tlct2/convert/concepts.hpp"
#include "tlct2/convert/tspc/multiview.hpp"
#include "tlct2/convert/tspc/patchsize.hpp"
#include "tlct2/convert/tspc/state.hpp"

namespace tlct2::cvt::tspc {

namespace _ = _cvt::tspc;

using _::Neighbors;
using _::State;

static_assert(tlct2::cvt::concepts::CNeighbors<Neighbors>);

} // namespace tlct2::cvt::tspc
