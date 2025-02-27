#pragma once

#include <numbers>

#include <opencv2/core.hpp>

#include "tlct1/common/defines.h"
#include "tlct1/config/concepts.hpp"
#include "tlct1/config/tspc/calib.hpp"

namespace tlct1::_cfg::tspc {

class SpecificConfig
{
public:
    static constexpr int DEFAULT_UPSAMPLE = 2;
    static constexpr double DEFAULT_PSIZE_INFLATE = std::numbers::sqrt3 * 1.5;
    static constexpr double DEFAULT_MAX_PSIZE = 0.5;
    static constexpr double DEFAULT_PATTERN_SIZE = 0.325;
    static constexpr int DEFAULT_PSIZE_SHORTCUT_THRESHOLD = 4;

    static constexpr double GRADIENT_BLENDING_WIDTH = 0.75;

    // Constructor
    TLCT1_API inline SpecificConfig() noexcept
        : imgsize_(), upsample_(DEFAULT_UPSAMPLE), psize_inflate_(DEFAULT_PSIZE_INFLATE),
          max_psize_(std::min(DEFAULT_MAX_PSIZE, 1.0 / DEFAULT_PSIZE_INFLATE)), pattern_size_(DEFAULT_PATTERN_SIZE),
          psize_shortcut_threshold_(DEFAULT_PSIZE_SHORTCUT_THRESHOLD){};
    TLCT1_API inline SpecificConfig(const SpecificConfig& rhs) noexcept = default;
    TLCT1_API inline SpecificConfig& operator=(const SpecificConfig& rhs) noexcept = default;
    TLCT1_API inline SpecificConfig(SpecificConfig&& rhs) noexcept = default;
    TLCT1_API inline SpecificConfig& operator=(SpecificConfig&& rhs) noexcept = default;
    TLCT1_API inline SpecificConfig(cv::Size imgsize, int upsample, double psize_inflate, double max_psize,
                                    double pattern_size, int psize_shortcut_threshold) noexcept
        : imgsize_(imgsize), upsample_(upsample), psize_inflate_(psize_inflate),
          max_psize_(std::min(max_psize, 1.0 / psize_inflate)), pattern_size_(pattern_size),
          psize_shortcut_threshold_(psize_shortcut_threshold){};

    // Initialize from
    [[nodiscard]] TLCT1_API static inline SpecificConfig fromConfigMap(const ConfigMap& cfg_map);

    // Const methods
    [[nodiscard]] TLCT1_API inline cv::Size getImgSize() const noexcept { return imgsize_; };
    [[nodiscard]] TLCT1_API inline int getUpsample() const noexcept { return upsample_; };
    [[nodiscard]] TLCT1_API inline double getPsizeInflate() const noexcept { return psize_inflate_; };
    [[nodiscard]] TLCT1_API inline double getMaxPsize() const noexcept { return max_psize_; };
    [[nodiscard]] TLCT1_API inline double getPatternSize() const noexcept { return pattern_size_; };
    [[nodiscard]] TLCT1_API inline int getPsizeShortcutThreshold() const noexcept { return psize_shortcut_threshold_; };

private:
    double psize_inflate_;
    double max_psize_;
    double pattern_size_;
    int psize_shortcut_threshold_;
    cv::Size imgsize_;
    int upsample_;
};

static_assert(concepts::CSpecificConfig<SpecificConfig>);

SpecificConfig SpecificConfig::fromConfigMap(const ConfigMap& cfg_map)
{
    const auto width = cfg_map.get<int, "width">();
    const auto height = cfg_map.get<int, "height">();
    const auto upsample = cfg_map.get<int, "upsample", DEFAULT_UPSAMPLE>();
    const auto psize_inflate = cfg_map.get<double, "psizeInflate", DEFAULT_PSIZE_INFLATE>();
    const auto max_psize = cfg_map.get<double, "maxPsize", DEFAULT_MAX_PSIZE>();
    const auto pattern_size = cfg_map.get<double, "patternSize", DEFAULT_PATTERN_SIZE>();
    const auto psize_shortcut_threshold =
        cfg_map.get<int, "psizeShortcutThreshold", DEFAULT_PSIZE_SHORTCUT_THRESHOLD>();
    return {{width, height}, upsample, psize_inflate, max_psize, pattern_size, psize_shortcut_threshold};
}

} // namespace tlct1::_cfg::tspc
