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

#ifndef _EXPRESSION_HPP_
#define _EXPRESSION_HPP_

#include <string>
#include "tree.hpp"

template <typename T> class Tree;

/**
 * Namespace holding expression resources
 */ 
namespace Expr {

    enum Type {
        VAR,
        NUMBER,
        ADD,
        IMUL,
        SUB,
        IDIV,
        MOD,
        POW,
        ASSIGN
    };

    /**
     * Tree node representation
     */ 
    struct Node {
        Type type;
        std::string text;
        Node() {}
        Node(Type type, std::string text) : type(type), text(text) {}
    };

    using Expression = Tree<Node>;

    std::ostream& operator<< (std::ostream &out, const Expr::Node& node);
    std::ostream& operator<< (std::ostream &out, const Expr::Type& type);

}



#endif//_EXPRESSION_HPP_