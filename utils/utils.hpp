/**
 * @file utils.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Internal utilities
 * 
 * Contains functions to make working with internal structures and types easier
 */

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>
#include <set>
#include "arg_parser.hpp"

/** Utils namespace */
namespace Utils {
    
    /**
     * Converts string to uppercase
     * @param text Text to be converted
     * @return text in uppercase
     */
    std::string to_upper(std::string text);

    /**
     * Converts all elements to uppercase
     * @param text Values to be converted
     */
    void to_upper(std::vector<std::string> *text);

    /**
     * Converts string to lowercase
     * @param text Text to be converted
     * @return text in lowercase
     */
    std::string to_lower(std::string text);

    /**
     * Capializes string (makes first letter capital)
     * @param text Text to capitalize
     * @return Capitalized text
     */ 
    std::string capitalize(std::string text);

    /**
     * Parses csv values
     * @param csv String of csv values
     * @param delim CSV delimiter. Comma by default.
     * @return Set of these value
     */
    std::set<std::string> split_csv(std::string csv, char delim=','); 

    /**
     * Sanitizes text by removing escape characters with their written out form
     * @param text Text to sanitize
     */ 
    std::string sanitize(const std::string &text);

    /**
     * @return true If timeout has approached
     * @return false If timeout hasn't yet happened
     */
    inline bool is_timeout() {
        return Args::arg_opts.timeout > 0 
               && (std::chrono::steady_clock::now() - Args::arg_opts.start_time >= std::chrono::seconds(Args::arg_opts.timeout));
    }

    /**
     * @param fitness Programs fitness
     * @return true If precision is set and fitness is precise enouh
     * @return false Otherwise
     */
    inline bool is_precise(float fitness) {
        return Args::arg_opts.precision > 0 && static_cast<unsigned>((fitness * 100)) >= Args::arg_opts.precision;
    }
}

/**
 * Namespace containing all functions for working with types
 * and namely for type casting
 */ 
namespace Cast {
    /**
     * Method for casting to other types
     * @note has to be specialized, otherwise Error::error is called
     * @throw Exception::EbeTypeException when unable to cast
     * @param v Value
     */
    template<typename T>
    T to(std::string v);

    /// @note Default base (base 10) is used
    template<> unsigned int to(std::string v);

    /// @note Default base (base 10) is used
    template<> int to(std::string v);

    template<> float to(std::string v);
}

#endif//_UTILS_HPP_
