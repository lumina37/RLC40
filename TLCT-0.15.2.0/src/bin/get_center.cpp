#include <iostream>

#include "tlct2.hpp"

namespace tn = tlct2::tspc;

int main(int argc, char* argv[])
{
    const auto cfg_map = tlct2::ConfigMap::fromPath(argv[1]);
    const int row = std::stoi(argv[2]);
    const int col = std::stoi(argv[3]);

    if (cfg_map.getPipelineType() == tlct2::PipelineType::RLC) {
        const auto param_cfg = tn::ParamConfig::fromConfigMap(cfg_map);
        const auto layout = tn::Layout::fromCalibAndSpecConfig(param_cfg.getCalibCfg(), param_cfg.getSpecificCfg());
        const auto center = layout.getMICenter(row, col);
        std::cout << center << std::endl;
    } else {
        const auto param_cfg = tn::ParamConfig::fromConfigMap(cfg_map);
        const auto layout = tn::Layout::fromCalibAndSpecConfig(param_cfg.getCalibCfg(), param_cfg.getSpecificCfg());
        const auto center = layout.getMICenter(row, col);
        std::cout << center << std::endl;
    }
}
