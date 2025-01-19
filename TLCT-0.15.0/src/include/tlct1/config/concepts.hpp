#pragma once

#include "tlct1/config/concepts/calib.hpp"
#include "tlct1/config/concepts/factory.hpp"
#include "tlct1/config/concepts/layout.hpp"
#include "tlct1/config/concepts/specific.hpp"

namespace tlct1::cfg::concepts {

namespace _ = _cfg::concepts;

using _::CCalibConfig;
using _::CLayout;
using _::CSpecificConfig;
using _::is_factory_of;

} // namespace tlct1::cfg::concepts
