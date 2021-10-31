/**
 * @file scanner.cpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Syntactical analysis base class
 * 
 * Base scanner class
 */

#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <cstddef>
#include "scanner.hpp"
#include "ir.hpp"
#include "instruction.hpp"
#include "arg_parser.hpp"
#include "utils.hpp"
#include "exceptions.hpp"

#include <iostream>

Scanner::Scanner(const char *scanner_name) : Compiler(scanner_name) {

}
