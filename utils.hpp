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
}

namespace Cast {
    /**
     * Method for casting to other types
     * @note has to be specialized, otherwise error
     * @param v Value
     */
    template<typename T>
    T to(std::string v);

    /**
     * Method for casting to uint
     * @param v Value
     * @return v converted
     */
    template<> unsigned int to(std::string v);
}

#endif//_UTILS_HPP_
