/**
 * @file logging.cpp
 * @author Marek Sedlacek
 * @date September 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Info logging and statistics logging
 * 
 * Handles compilation and statistics loggings
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "logging.hpp"
#include "compiler.hpp"

// Unit names definitions
const std::string Analytics::UnitNames::JENN_FITNESS = "jenn_fitness";
const std::string Analytics::UnitNames::MIRANDA_FITNESS = "miRANDa_fitness";

BaseLogger::BaseLogger() : disable(false), log_everything(false), logging_level{0} {

}

BaseLogger::~BaseLogger() {
    for(auto s: streams){
        s->flush();
    }
}

Logger::Logger() : BaseLogger() {
    streams.push_back(&std::cerr);
}

Logger::~Logger() {
    
}

Logger &Logger::get() {
    static Logger instance;
    return instance;
}

void Logger::debug(unsigned level, const std::string &file_func, const std::string &message) {
    if (disable || level > logging_level) {
        return;
    }
    // Check if function has logging enabled
    if (!log_everything) {
        if(enabled.find(file_func) == enabled.end()){
            return;
        }
    }
    // Output log to all registered streams
    for (auto s: streams) {
        (*s) << std::boolalpha << file_func << ": " << message << std::endl;
    }
}

Analytics::Analytics() : BaseLogger() {

}

Analytics::~Analytics() {
    // Release allocated streams
    for (const auto[unit, stream] : stream_map) {
        stream->flush();
        delete stream;
    }
}

void Analytics::log(const std::string &unit, const std::string &attr, const std::string &value) {
    if (disable) {
        return;
    }
    // Check if all statistics should be logged
    if (!log_everything) {
        if (enabled.find(unit) == enabled.end()) {
            return;
        }
    }

    (*stream_map[unit]) << attr << "," << value << std::endl; 
}

Analytics &Analytics::get() {
    static Analytics instance;
    return instance;
}

void Analytics::set_enabled(std::set<std::string> enabled) { 
    this->enabled = enabled; 
}

void Analytics::open_streams() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream timess;
    timess << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    std::string time = timess.str();
    // Open all enabled as streams
    for(auto unit: enabled) {
        auto file_name = folder_path+std::string("/")+unit+"_"+time+".csv";
        auto stream = new std::ofstream((file_name).c_str(), std::ios::out);
        if(!stream->is_open()) {
            Error::error(Error::ErrorCode::FILE_ACCESS, 
                         (std::string("Could not create analytics file '")+file_name+"'").c_str());
        }
        this->stream_map[unit] = stream;
    }
}
