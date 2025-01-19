#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "enums.hpp"
#include "tlct0/common/defines.h"

namespace tlct0::cfg {

class ConfigMap
{
public:
    // Typename alias
    using TMap = std::map<std::string, std::string>;

    // Constructor
    TLCT0_API inline ConfigMap() : map_(){};
    TLCT0_API inline ConfigMap& operator=(const ConfigMap& rhs) = default;
    TLCT0_API inline ConfigMap(const ConfigMap& rhs) = default;
    TLCT0_API inline ConfigMap& operator=(ConfigMap&& rhs) noexcept = default;
    TLCT0_API inline ConfigMap(ConfigMap&& rhs) noexcept = default;
    TLCT0_API explicit inline ConfigMap(TMap cfg_map) : map_(std::move(cfg_map)){};

    // Initialize from
    [[nodiscard]] TLCT0_API static inline ConfigMap fromPath(const std::string_view& path);

    // Const methods
    [[nodiscard]] TLCT0_API inline bool isEmpty() const noexcept;
    [[nodiscard]] TLCT0_API inline PipelineType getPipelineType() const noexcept;
    [[nodiscard]] TLCT0_API inline const TMap& getMap() const noexcept;

private:
    TMap map_;
};

ConfigMap ConfigMap::fromPath(const std::string_view& path)
{
    std::ifstream fs(path.data());
    if (!fs) {
        std::cerr << "Failed to load `" << typeid(ConfigMap).name() << "` from `" << path << "`!" << std::endl;
        return {};
    }

    std::map<std::string, std::string> cfg_map;
    std::string row;
    while (std::getline(fs, row)) {
        if (row.empty() || row.starts_with('=')) {
            break;
        }
        std::istringstream srow(row);
        std::string key, value;
        srow >> key;
        srow >> value;
        cfg_map[key] = value;
    }

    return ConfigMap(cfg_map);
}

bool ConfigMap::isEmpty() const noexcept { return map_.empty(); }

PipelineType ConfigMap::getPipelineType() const noexcept
{
    const auto it = map_.find("pipeline");
    if (it == map_.end()) {
        return PipelineType::RLC;
    }
    const std::string& val = it->second;
    const int ival = std::stoi(val);
    return (PipelineType)ival;
}

const ConfigMap::TMap& ConfigMap::getMap() const noexcept { return map_; }

} // namespace tlct0::cfg
