/**
 * @file Message.hpp
 * @author saivishwak
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <string>
#include <vector>
#include "Block.hpp"
#include <json/json.h>

namespace msg {

    /**
     * @brief Class to handle marshalling and unmarshalling of network messages
     * 
     */
    class Message {
    public:
        Message();
        static std::string marshall(Block body);
        static std::string marshall(std::string message, std::string type);
        static std::string marshall(std::string message, std::string type, std::vector<int> peers);
        static Block unmarshall(std::string buffer);
        static Json::Value unmarshall(std::string buffer, int type);
    };
}