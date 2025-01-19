#pragma once

#include <concepts>
#include <ranges>

#include <opencv2/core.hpp>

#include "tlct0/config/concepts.hpp"

namespace tlct0::cvt::concepts {

namespace rgs = std::ranges;
namespace tcfg = tlct0::cfg;

template <typename Self>
concept CState = requires {
    // Initialize from
    requires requires(const Self::TLayout& layout, int views) {
        tcfg::concepts::CLayout<typename Self::TLayout>;
        { Self::fromLayoutAndViews(layout, views) } -> std::same_as<Self>;
    };
} && requires {
    // Non-const methods
    requires requires(Self self, const cv::Mat& newsrc) { self.feed(newsrc); };
} && requires {
    // Iterator
    rgs::forward_range<Self>;
    std::convertible_to<decltype(std::declval<Self>().begin()), cv::Mat>;
    std::convertible_to<decltype(std::declval<Self>().end()), cv::Mat>;
};

} // namespace tlct0::cvt::concepts