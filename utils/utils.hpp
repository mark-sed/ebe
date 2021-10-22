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
}

#endif//_UTILS_HPP_
