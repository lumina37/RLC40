#pragma once

#include "tspc/calib.hpp"
#include "tspc/layout.hpp"
#include "tspc/param.hpp"
#include "tspc/specific.hpp"

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
