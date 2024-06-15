/**
 * @file Block.hpp
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

namespace msg {
    struct Block {
        std::string message;
        std::vector<int> ports;
        std::string type;

        /**
         * @brief Construct a new Block object needed for compiling
         * 
         */
        Block() {};

        std::string getType(){
            return this->type;
        }
    };
}