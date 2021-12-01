/**
 * @file tree.hpp
 * @author Marek Sedlacek
 * @date November 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Tree data structure
 * 
 * Tree for special IR representations.
 */

#ifndef _TREE_HPP_
#define _TREE_HPP_

#include <vector>
#include <ostream>
#include "expression.hpp"

namespace Expr {
    class Node;
}

/**
 * Tree data structure
 */ 
template <typename T>
class Tree {
public:
    T value;                         ///< Value of the node
    std::vector<Tree<T> > children;  ///< Node's children

    Tree() {}
    Tree(T value, std::vector<Tree<T> > children) : value(value), children(children) {}
    
    void dbprint(std::ostream &out);
};


#endif//_TREE_HPP_