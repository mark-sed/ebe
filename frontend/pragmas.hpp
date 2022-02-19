/**
 * @file pragmas.hpp
 * @author Marek Sedlacek
 * @date February 2021
 * @copyright Copyright 2022 Marek Sedlacek. All rights reserved.
 * 
 * @brief Ebel pragmas handeling and parsing
 * 
 * Parses and sets ebel pragmas
 */

#ifndef _PRAGMAS_HPP_
#define _PRAGMAS_HPP_

#include "ir.hpp"

namespace IR {
    class EbelNode;
}

namespace Pragma {
/**
 * @brief Holds all possible pragmas
 */
class Pragmas {
private:
    IR::EbelNode *ebel;  ///< Ebel for which these pragmas are set

    int sym_table_size;  ///< Symbol table size pragma

    /** Splits pragma into vector of values */
    std::vector<std::string> split_pragma(std::string value);
public:
    /** Constructor */
    Pragmas(IR::EbelNode *ebel);
    Pragmas(const Pragmas &other, IR::EbelNode *ebel);
    Pragmas() = delete;
    Pragmas(const Pragmas &other) = delete;
    /** Destructor */
    ~Pragmas() {}

    /**
     * @brief Parses pragma
     * 
     * @param value Pragma value. Should be only the string after "@pragma"
     * @param scanner Parent ebel scanner.
     */
    void parse(std::string value);

    /**
     * @brief Applies parsed pragmas
     */
    void apply();
};
}

#endif//_PRAGMAS_HPP_