#pragma once

#include <cmath>
#include <numbers>
#include <ranges>

#include <opencv2/imgproc.hpp>

#include "tlct2/config/tspc.hpp"
#include "tlct2/convert/helper.hpp"
#include "tlct2/convert/tspc/patchsize/params.hpp"

namespace tlct2::_cvt::tspc {

namespace rgs = std::ranges;
namespace tcfg = tlct2::cfg::tspc;

static inline void renderView(const cv::Mat& src, cv::Mat& dst, const tcfg::Layout& layout,
                              const std::vector<PsizeRecord>& patchsizes, const MvParams& params, MvCache& cache,
                              int view_row, int view_col)
{
    const int view_shift_x = (view_col - params.views / 2) * params.view_interval;
    const int view_shift_y = (view_row - params.views / 2) * params.view_interval;

    cache.render_canvas.setTo(std::numeric_limits<float>::epsilon());
    cache.weight_canvas.setTo(std::numeric_limits<float>::epsilon());

    cv::Mat rotated_patch, resized_patch;
    cv::Mat resized_patch_channels[MvCache::CHANNELS];
    cv::Mat weighted_patch;

    int row_offset = 0;
    for (const int row : rgs::views::iota(0, layout.getMIRows())) {

        int offset = row_offset;
        for (const int col : rgs::views::iota(0, layout.getMICols(row))) {
            const cv::Point2d center = layout.getMICenter(row, col);

            // Extract patch
            const double psize = params.psize_inflate * patchsizes[offset].psize;
            const cv::Point2d patch_center{center.x + view_shift_x, center.y + view_shift_y};
            const cv::Mat& patch = getRoiImageByCenter(src, patch_center, psize);

            // Paste patch
            cv::rotate(patch, rotated_patch, cv::ROTATE_180);
            cv::resize(rotated_patch, resized_patch, {params.resized_patch_width, params.resized_patch_width}, 0, 0,
                       cv::INTER_LINEAR);

            cv::split(resized_patch, resized_patch_channels);
            for (cv::Mat& resized_patch_channel : resized_patch_channels) {
                cv::multiply(resized_patch_channel, cache.grad_blending_weight, resized_patch_channel);
            }

            cv::merge(resized_patch_channels, MvCache::CHANNELS, weighted_patch);

            // if the second bar is not out shift, then we need to shift the 1 col
            // else if the second bar is out shift, then we need to shift the 0 col
            const int right_shift = ((row % 2) ^ (int)layout.isOutShift()) * (params.patch_xshift / 2);
            const cv::Rect roi{col * params.patch_xshift + right_shift, row * params.patch_yshift,
                               params.resized_patch_width, params.resized_patch_width};
            cache.render_canvas(roi) += weighted_patch;
            cache.weight_canvas(roi) += cache.grad_blending_weight;

            offset++;
        }

        row_offset += layout.getMIMaxCols();
    }

    cv::Mat cropped_rendered_image = cache.render_canvas(params.canvas_crop_roi);
    cv::Mat cropped_weight_matrix = cache.weight_canvas(params.canvas_crop_roi);

    cv::split(cropped_rendered_image, cache.cropped_rendered_image_channels);
    for (cv::Mat& cropped_new_image_channel : cache.cropped_rendered_image_channels) {
        cropped_new_image_channel /= cropped_weight_matrix;
    }
    cv::Mat& normed_image = cropped_rendered_image;
    cv::merge(cache.cropped_rendered_image_channels, MvCache::CHANNELS, normed_image);

    normed_image.convertTo(cache.normed_image_u8, CV_8UC3);
    cv::resize(cache.normed_image_u8, cache.resized_normed_image_u8, {params.output_width, params.output_height}, 0.0,
               0.0, cv::INTER_AREA);

    if (layout.getRotation() > std::numbers::pi / 4.0) {
        cv::transpose(cache.resized_normed_image_u8, dst);
    } else {
        dst = std::move(cache.resized_normed_image_u8);
    }
}

} // namespace tlct2::_cvt::tspc
