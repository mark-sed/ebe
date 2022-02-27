/**
 * @file expression.hpp
 * @author Marek Sedlacek
 * @date November 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Expression handeling
 * 
 * Resources for representing and working with expressions.
 */

#include "expression.hpp"

namespace Expr{
    std::ostream& operator<< (std::ostream &out, const Expr::Node& node) {
        out << "(" << node.type << ") " << node.text << std::endl;
        return out;
    }

    std::ostream& operator<< (std::ostream &out, const Expr::Type& type) {
        const char *NAMES[] = {
            "VAR",
            "NUMBER",
            "FLOAT",
            "TEXT",
            "ADD",
            "IMUL",
            "SUB",
            "IDIV",
            "MOD",
            "POW",
            "EQ"
        };
        constexpr int names_size = sizeof(NAMES)/sizeof(char *);
        if(type >= names_size){
            return out << "unknown";
        }
        return out << NAMES[type];
    }
}
