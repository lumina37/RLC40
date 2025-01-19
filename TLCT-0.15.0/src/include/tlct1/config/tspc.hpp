#pragma once

#include "tlct1/config/tspc/calib.hpp"
#include "tlct1/config/tspc/layout.hpp"
#include "tlct1/config/tspc/param.hpp"
#include "tlct1/config/tspc/specific.hpp"

namespace tlct1::cfg::tspc {

namespace _ = _cfg::tspc;

using _::CalibConfig;
using _::Layout;
using _::ParamConfig;
using _::SpecificConfig;

} // namespace tlct1::cfg::tspc

namespace tlct1::_cfg {

template class ParamConfig_<tlct1::cfg::tspc::Layout>;

}
