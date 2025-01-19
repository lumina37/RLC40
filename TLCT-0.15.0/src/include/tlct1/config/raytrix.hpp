#pragma once

#include "tlct1/config/raytrix/calib.hpp"
#include "tlct1/config/raytrix/layout.hpp"
#include "tlct1/config/raytrix/param.hpp"
#include "tlct1/config/raytrix/specific.hpp"

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
