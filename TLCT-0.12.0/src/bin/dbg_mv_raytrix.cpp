#include <filesystem>
#include <sstream>

#include <opencv2/imgcodecs.hpp>

#include "tlct0.hpp"

namespace fs = std::filesystem;
namespace tcfg = tlct0::cfg::raytrix;
namespace tcvt = tlct0::cvt::raytrix;

int main(int argc, char* argv[])
{
    const auto cfg_map = tlct0::cfg::ConfigMap::fromPath(argv[1]);
    const auto param_cfg = tcfg::ParamConfig::fromConfigMap(cfg_map);
    const auto& common_cfg = param_cfg.getCommonCfg();

    constexpr int upsample = 4;
    const auto layout =
        tcfg::Layout::fromCfgAndImgsize(param_cfg.getCalibCfg(), param_cfg.getImgSize()).upsample(upsample);
    auto state = tcvt::State::fromLayoutAndViews(layout, common_cfg.getViews());

    const cv::Range range = common_cfg.getRange();
    for (int i = range.start; i <= range.end; i++) {
        const auto srcpath = common_cfg.fmtSrcPath(i);
        state.feed(cv::imread(srcpath.string()));

        int img_cnt = 1;
        const auto dstdir = common_cfg.fmtDstPath(i);
        fs::create_directories(dstdir);

        for (const auto& mv : state) {
            std::stringstream filename_s;
            filename_s << "image_" << std::setw(3) << std::setfill('0') << img_cnt << ".png";
            const fs::path saveto_path = dstdir / filename_s.str();
            cv::imwrite(saveto_path.string(), mv);
            img_cnt++;
        }
    }
}
