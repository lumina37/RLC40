#pragma once

#include "tlct2/config/tspc/calib.hpp"
#include "tlct2/config/tspc/layout.hpp"
#include "tlct2/config/tspc/param.hpp"
#include "tlct2/config/tspc/specific.hpp"

namespace tlct2 {

namespace cfg::tspc {

namespace _ = _cfg::tspc;

using _::CalibConfig;
using _::Layout;
using _::ParamConfig;
using _::SpecificConfig;

} // namespace cfg::tspc

namespace _cfg {

template class ParamConfig_<tlct2::cfg::tspc::Layout>;

}

} // namespace tlct2
