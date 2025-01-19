#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "tlct0/common/defines.h"

namespace tlct0::cvt::_hp {

static double computeGrad(const cv::Mat& src)
{
    cv::Mat edges;
    double weight = 0.0;
    cv::Sobel(src, edges, CV_16S, 1, 0);
    edges = cv::abs(edges);
    weight += cv::sum(edges)[0];
    cv::Sobel(src, edges, CV_16S, 0, 1);
    edges = cv::abs(edges);
    weight += cv::sum(edges)[0];
    weight /= edges.size().area();
    return weight;
}

} // namespace tlct0::cvt::_hp
