#pragma once

#include <concepts>

#include <opencv2/core.hpp>

#include "tlct1/config/concepts.hpp"
#include "tlct1/convert/patchsize/direction.hpp"

namespace tlct1::_cvt::concepts {

namespace tcfg = tlct1::cfg;

template <typename Self>
concept CNeighbors = requires {
    // Initialize from
    requires requires(const Self::TLayout& layout, const cv::Point index) {
        requires tcfg::concepts::CLayout<typename Self::TLayout>;
        { Self::fromLayoutAndIndex(layout, index) } noexcept -> std::same_as<Self>;
    };
} && requires {
    requires requires(const Self& self) {
        { self.getSelfIdx() } noexcept -> std::same_as<cv::Point>;
        { self.getSelfPt() } noexcept -> std::same_as<cv::Point2d>;

        { self.hasNeighbor(Direction::LEFT) } noexcept -> std::same_as<bool>;
        { self.getNeighborIdx(Direction::LEFT) } noexcept -> std::same_as<cv::Point>;
        { self.getNeighborPt(Direction::LEFT) } noexcept -> std::same_as<cv::Point2d>;
        { self.getUnitShift(Direction::LEFT) } noexcept -> std::same_as<cv::Point2d>;
    };
};

} // namespace tlct1::_cvt::concepts
