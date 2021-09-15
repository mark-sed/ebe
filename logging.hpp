/**
 * @file logging.hpp
 * @author Marek Sedlacek
 * @date September 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Info logging and statistics logging
 * 
 * Handles compilation and statistics loggings
 */

#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

#include <sstream>
#include <string>
#include <vector>
#include <ostream>
#include <set>
#include <algorithm>
#include "utils.hpp"


/**
 * Base class for all loggers
 */ 
class BaseLogger {
protected:
    bool disable;
    bool log_everything;
    unsigned logging_level;
    std::vector<std::ostream *> streams;
public:
    /** Constructor */
    BaseLogger();
    /** 
     * Destructor. 
     * Flushes streams 
     */
    ~BaseLogger();

    /**
     * Setter for disabling
     * @param disable If true, the logger will be disabled
     */
    void set_disable(bool disable) { this->disable=disable; }

    /**
     * Sets logging level to be printed
     * @param level Verbosity level
     */ 
    void set_logging_level(unsigned level) { this->logging_level = level; }

    /**
     * Adds a new initialized ostream to log to
     */ 
    void add_stream(std::ostream *stream) { this->streams.push_back(stream); }

    /**
     * Setter for logging everything
     * @param log_everything new value
     */ 
    void set_log_everything(bool log_everything) { this->log_everything = log_everything; }
};


/**
 * Class for debugging logs
 */ 
class Logger : public BaseLogger {
private:
    std::set<std::string> enabled;
public:
    /// Default constructor for get instance
    Logger();
    ~Logger();

    /**
     * @return logger instance 
     */ 
    static Logger &get();

    /**
     * Debug logging
     * @param level Verbosity level
     * @param file __FILE__ should be passed here or the file name
     * @param message Message to print
     */
    void debug(unsigned level, const std::string &file_func, const std::string &message);

    
    /**
     * Set file::functions to output to log
     * @param enabled Set of file::function names
     */
    void set_enabled(std::set<std::string> enabled) { this->enabled = enabled; }
};


/**
 * Analytics class for logging statistical and other info
 */ 
class Analytics : public BaseLogger {
public:
    /** Constructor */
    Analytics();
    ~Analytics();
    // TODO: Add anlytics functions
};

/// Tabs for logging
#define TAB1 "\t"
#define TAB2 TAB1 TAB1
#define TAB3 TAB2 TAB1
#define TAB4 TAB3 TAB1
#define TAB5 TAB4 TAB1

/// Maximum logging level
#ifndef MAX_LOGGING_LEVEL
#define MAX_LOGGING_LEVEL 5
#endif

/// Logging macro
#ifndef DISABLE_LOGGING
    /// @param message Can be even stream
    #define LOG(level, message) if ((level) <= MAX_LOGGING_LEVEL) { \
        std::stringstream out; \
        out << message; \
        Logger::get().debug(level, std::string(__FILE__)+std::string("::")+std::string(__func__), out.str()); }
    /// Logs whole container
    #define LOG_CONT(level, message, container) if ((level) <= MAX_LOGGING_LEVEL) { \
        std::stringstream out; \
        out << message << std::endl; \
        for(auto v: (container)) { out << TAB1 << v << std::endl; } \
        Logger::get().debug(level, std::string(__FILE__)+std::string("::")+std::string(__func__), out.str()); }
    /// Logs container of strings which will be sanitized (removes escape sequences)
    #define LOG_CONT_SANITIZE(level, message, container) if ((level) <= MAX_LOGGING_LEVEL) { \
        std::stringstream out; \
        out << message << std::endl; \
        for(auto v: (container)) { out << Utils::sanitize(v) << std::endl; } \
        Logger::get().debug(level, std::string(__FILE__)+std::string("::")+std::string(__func__), out.str()); }
#else
    #define LOG(level, message)
    #define LOG_CONT(level, message, container)
    #define LOG_CONT_SANITIZE(level, message, container)
#endif

#define LOG1(message) LOG(1, message)
#define LOG2(message) LOG(2, message)
#define LOG3(message) LOG(3, message)
#define LOG4(message) LOG(4, message)
#define LOG5(message) LOG(5, message)
#define LOGMAX(message) LOG(MAX_LOGGING_LEVEL, message)

#endif//_LOGGING_HPP_