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
#include <sstream>
#include <regex>
#include "utils.hpp"
#include "exceptions.hpp"
#include "backend/compiler.hpp"

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

std::set<std::string> Utils::split_csv(std::string csv, char delim) {
    std::set<std::string> splitted;
    std::string value;
    std::stringstream csv_stream(csv);
    while(std::getline(csv_stream, value, delim)){
        splitted.insert(value);
    }
    return splitted;
}

std::string Utils::sanitize(const std::string &text) {
    const std::string ESC_CHARS("\t\n\v\a\b\f\r\\");
    std::string sanitized;
    for (std::string::size_type i = 0; i < text.size(); i++) {
        if (ESC_CHARS.find(text[i]) == std::string::npos){
            sanitized.push_back(text[i]);
        }
        else{
            sanitized.push_back('\\');
            switch(text[i]){
                case '\n': sanitized.push_back('n');
                break;
                case '\t': sanitized.push_back('t');
                break;
                case '\r': sanitized.push_back('r');
                break;
                case '\v': sanitized.push_back('v');
                break;
                case '\\': sanitized.push_back('\\');
                break;
                default: sanitized += std::to_string(static_cast<int>(text[i]));
                break;
            }
        }
    }
    return sanitized;
}

template<typename T>
T Cast::to(std::string v){
    Error::error(Error::ErrorCode::INTERNAL, "Unknown argument type conversion");
}

template<> unsigned int Cast::to(std::string v){
    try{
        return std::stoul(v);
    }catch (std::exception & e){
        throw Exception::EbeTypeException(std::string("Could not convert value \""+v+"\" to unsigned int"));
    }
}
