/**
 * @file utils.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Internal utilities
 * 
 * Contains functions to make working with internal structures and types easier
 */

#include <algorithm>
#include "utils.hpp"
#include "compiler.hpp"

using namespace Utils;
using namespace Cast;

std::string Utils::to_upper(std::string text){
    std::string outs(text.length(), '\0');
    std::transform(text.begin(), text.end(), outs.begin(), ::toupper);
    return outs;
}

void Utils::to_upper(std::vector<std::string> *text){
    for(auto &v: *text){
        std::transform(v.begin(), v.end(), v.begin(), ::toupper);
    }
}

template<typename T>
T Cast::to(std::string v){
    Error::error(Error::ErrorCode::INTERNAL, "Unknown argument type conversion");
}

template<> unsigned int Cast::to(std::string v){
    try{
        return std::stoul(v);
    }catch (std::exception & e){
        Error::error(Error::ErrorCode::INTERNAL, "Incorrect argument type (could not be converted to unsigned integer)");
    }
}
