#pragma once

#include <concepts>

#include <opencv2/core.hpp>

#include "tlct2/config/concepts.hpp"

namespace tlct2::_cvt::concepts {

namespace tcfg = tlct2::cfg;

template <typename Self>
concept CNeighbors = requires {
    // Constant
    { Self::INFLATE } -> std::convertible_to<double>;
} && requires {
    // Initialize from
    requires requires(const Self::TLayout& layout, const cv::Point index) {
        requires tcfg::concepts::CLayout<typename Self::TLayout>;
        { Self::fromLayoutAndIndex(layout, index) } noexcept -> std::same_as<Self>;
    };
} && requires {
    requires requires(const Self& self) {
        { self.getSelfIdx() } noexcept -> std::same_as<cv::Point>;
        { self.getSelfPt() } noexcept -> std::same_as<cv::Point2d>;

        { self.hasNeighbor((typename Self::Direction)0) } noexcept -> std::same_as<bool>;
        { self.getNeighborIdx((typename Self::Direction)0) } noexcept -> std::same_as<cv::Point>;
        { self.getNeighborPt((typename Self::Direction)0) } noexcept -> std::same_as<cv::Point2d>;
        { self.getUnitShift((typename Self::Direction)0) } noexcept -> std::same_as<cv::Point2d>;
    };
};

} // namespace tlct2::_cvt::concepts
