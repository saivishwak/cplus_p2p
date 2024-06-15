/**
 * @file Config.hpp
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>
#include <spdlog/spdlog.h>

namespace Utils {
    /**
     * @brief Config class to read config.json and store data
     * 
     */
    class Config {
    public:
        std::vector<int> seedPorts;
        Json::Value rootNode;
        Config(std::string path);
    };
}
