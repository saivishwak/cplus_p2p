/**
 * @file Config.cpp
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Config.hpp"

/**
 * @brief Construct a new Utils:: Config:: Config object
 * 
 * @param path 
 */
Utils::Config::Config(std::string path) {
  Json::Value root;
  Json::Reader reader;
  std::ifstream file(path);

  if (reader.parse(file, root)) {
    this->rootNode = root;
    const Json::Value seedPorts = root["seedPorts"];
    spdlog::info("Config File -> {}", root.toStyledString());
    for (auto x : seedPorts) {
      this->seedPorts.push_back(x.asInt());
    }
  }
  else {
    spdlog::error("Error parsing config.json");
    exit(0);
  }
}