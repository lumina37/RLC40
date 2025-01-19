#pragma once

#include <cstdint>

namespace tlct2::_cvt {

struct PsizeRecord {
    int psize;
    uint64_t hash;
};

struct PsizeMetric {
    int psize;
    double metric;
};

} // namespace tlct2::_cvt
