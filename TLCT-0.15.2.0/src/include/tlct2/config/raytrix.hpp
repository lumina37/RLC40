#pragma once

#include "tlct2/config/raytrix/calib.hpp"
#include "tlct2/config/raytrix/layout.hpp"
#include "tlct2/config/raytrix/param.hpp"
#include "tlct2/config/raytrix/specific.hpp"

namespace tlct2 {

namespace cfg::raytrix {

namespace _ = _cfg::raytrix;

using _::CalibConfig;
using _::Layout;
using _::LEN_TYPE_NUM;
using _::ParamConfig;
using _::SpecificConfig;

} // namespace cfg::raytrix

namespace _cfg {

template class ParamConfig_<tlct2::cfg::raytrix::Layout>;

}

} // namespace tlct2
