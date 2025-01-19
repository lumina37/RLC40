#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/quality.hpp>

#include "tlct0/common/defines.h"
#include "tlct0/config/tspc/layout.hpp"
#include "tlct0/convert/helper/grad.hpp"

namespace tlct0::cvt::_hp {

class AnchorWrapper
{
public:
    // Typename alias
    using TBase = cv::quality::QualitySSIM;

    // Constructor
    TLCT0_API AnchorWrapper& operator=(const AnchorWrapper& rhs) noexcept = default;
    TLCT0_API inline AnchorWrapper(const AnchorWrapper& rhs) noexcept = default;
    TLCT0_API AnchorWrapper& operator=(AnchorWrapper&& rhs) noexcept = default;
    TLCT0_API AnchorWrapper(AnchorWrapper&& rhs) noexcept = default;
    TLCT0_API inline AnchorWrapper(cv::Ptr<cv::quality::QualitySSIM>&& base, const double weight)
        : base_(std::move(base)), weight_(weight){};

    // Const methods
    [[nodiscard]] TLCT0_API inline double getWeight() const noexcept;
    [[nodiscard]] TLCT0_API inline double compare(const cv::Mat& rhs) const;

    // Init from
    [[nodiscard]] static inline AnchorWrapper fromRoi(const cv::Mat& roi);

private:
    cv::Ptr<TBase> base_;
    double weight_;
};

AnchorWrapper AnchorWrapper::fromRoi(const cv::Mat& roi)
{
    double weight = computeGrad(roi);
    auto base = TBase::create(roi);
    return {std::move(base), weight};
}

double AnchorWrapper::getWeight() const noexcept { return weight_; }

double AnchorWrapper::compare(const cv::Mat& rhs) const { return -base_->compute(rhs)[0]; }

} // namespace tlct0::cvt::_hp
