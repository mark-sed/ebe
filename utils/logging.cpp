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
#include "logging.hpp"

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
    if(disable || level > logging_level){
        return;
    }
    // Check if function has logging enabled
    if(!log_everything){
        if(enabled.find(file_func) == enabled.end()){
            return;
        }
    }
    // Output log to all registered streams
    for(auto s: streams){
        (*s) << file_func << ": " << message << std::endl;
    }
}

Analytics::Analytics() : BaseLogger() {

}

Analytics::~Analytics() {

}