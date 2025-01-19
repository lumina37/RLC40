#pragma once

#include "raytrix/calib.hpp"
#include "raytrix/layout.hpp"
#include "raytrix/param.hpp"
#include "raytrix/specific.hpp"

namespace tlct1::cfg::raytrix {

namespace _ = _cfg::raytrix;

using _::CalibConfig;
using _::Layout;
using _::LEN_TYPE_NUM;
using _::ParamConfig;
using _::SpecificConfig;

} // namespace tlct1::cfg::raytrix

namespace tlct1::_cfg {

template class ParamConfig_<tlct1::cfg::raytrix::Layout>;

}
