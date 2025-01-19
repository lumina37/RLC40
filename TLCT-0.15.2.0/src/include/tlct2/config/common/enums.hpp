#pragma once

#include <cstddef>

namespace tlct2::_cfg {

enum PipelineType {
    RLC,
    TLCT2,
    COUNT,
};

static constexpr int PIPELINE_COUNT = (int)PipelineType::COUNT;

} // namespace tlct2::_cfg
