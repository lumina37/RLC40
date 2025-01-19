#include <array>
#include <filesystem>
#include <ranges>
#include <sstream>

#include <argparse/argparse.hpp>
#include <opencv2/imgcodecs.hpp>

#include "tlct0.hpp"
#include "tlct1.hpp"
#include "tlct2.hpp"

namespace fs = std::filesystem;
namespace rgs = std::ranges;

template <tlct1::cvt::concepts::CState TState>
static inline void render1(const tlct1::cfg::ConfigMap& cfg_map)
{
    const auto param_cfg = TState::TParamConfig::fromConfigMap(cfg_map);
    const auto& generic_cfg = param_cfg.getGenericCfg();

    auto state = TState::fromParamCfg(param_cfg);

    const cv::Range range = generic_cfg.getRange();
    for (int i = range.start; i <= range.end; i++) {
        const auto srcpath = generic_cfg.fmtSrcPath(i);
        state.update(cv::imread(srcpath.string()));

        const auto dstdir = generic_cfg.fmtDstPath(i);
        fs::create_directories(dstdir);

        int img_cnt = 1;
        cv::Mat mv;
        for (const int view_row : rgs::views::iota(0, generic_cfg.getViews())) {
            for (const int view_col : rgs::views::iota(0, generic_cfg.getViews())) {
                std::stringstream filename_s;
                filename_s << "image_" << std::setw(3) << std::setfill('0') << img_cnt << ".png";
                const fs::path saveto_path = dstdir / filename_s.str();
                state.renderInto(mv, view_row, view_col);
                cv::imwrite(saveto_path.string(), mv);
                img_cnt++;
            }
        }
    }
}

template <tlct2::concepts::CState TState>
static inline void render2(const tlct2::ConfigMap& cfg_map)
{
    const auto param_cfg = TState::TParamConfig::fromConfigMap(cfg_map);
    const auto& generic_cfg = param_cfg.getGenericCfg();

    auto state = TState::fromParamCfg(param_cfg);

    const cv::Range range = generic_cfg.getRange();
    for (int i = range.start; i <= range.end; i++) {
        const auto srcpath = generic_cfg.fmtSrcPath(i);
        state.update(cv::imread(srcpath.string()));

        const auto dstdir = generic_cfg.fmtDstPath(i);
        fs::create_directories(dstdir);

        int img_cnt = 1;
        cv::Mat mv;
        for (const int view_row : rgs::views::iota(0, generic_cfg.getViews())) {
            for (const int view_col : rgs::views::iota(0, generic_cfg.getViews())) {
                std::stringstream filename_s;
                filename_s << "image_" << std::setw(3) << std::setfill('0') << img_cnt << ".png";
                const fs::path saveto_path = dstdir / filename_s.str();
                state.renderInto(mv, view_row, view_col);
                cv::imwrite(saveto_path.string(), mv);
                img_cnt++;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    argparse::ArgumentParser program("TLCT2", "v" TLCT2_VERSION, argparse::default_arguments::all);
    program.add_argument("param_file_path").help("the parameter file path").required();
    program.add_epilog(TLCT2_COMPILE_INFO);

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    const auto& param_file_path = program.get<std::string>("param_file_path");
    const auto cfg_map = tlct2::ConfigMap::fromPath(param_file_path);

    const int method = cfg_map.get<int, "method", 2>();

    if (method == 0) {
        namespace tcfg = tlct0::cfg::raytrix;
        namespace tcvt = tlct0::cvt::raytrix;

        const auto cfg_map = tlct0::cfg::ConfigMap::fromPath(param_file_path);
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
    } else if (method == 1) {
        const auto cfg_map = tlct1::cfg::ConfigMap::fromPath(param_file_path);
        render1<tlct1::raytrix::State>(cfg_map);
    } else if (method == 2) {
        render2<tlct2::tspc::State>(cfg_map);
    }
}
