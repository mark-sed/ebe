/**
 * @file scanner.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis
 * 
 * Handles scanning of input example files and ebel code as well
 * Each file type can have its own scanner which extends base Scanner class
 */

#ifndef _SCANNER_HPP_
#define _SCANNER_HPP_

#include <vector>
#include <string>
#include <istream>
#include <set>
#include <cstddef>
#include "ir.hpp"
#include "compiler.hpp"

class Scanner : public Compiler {
public:
    /** Constructor */
    Scanner(const char *scanner_name);
    virtual ~Scanner() {}

    /**
     * Does syntactical parsing of passed in text
     * @param text Example file's text parsed into vector of lines by preprocessor
     * @param file_name Example file's name for error information
     * @return Text parsed into IR node
     */
    virtual IR::Node *process(std::istream *text, const char *file_name) = 0;
};

#endif//_SCANNER_HPP_