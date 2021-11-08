/**
 * @file tree.cpp
 * @author Marek Sedlacek
 * @date November 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Tree data structure
 * 
 * Tree for special IR representations.
 */

#include "tree.hpp"
#include "expression.hpp"

template<typename T> 
void print_tree(std::ostream &out, const Tree<T> &tree, int space){
    const int LEVEL_SPACE = 12;
    space += LEVEL_SPACE;
    for(auto &c: tree.children){
        print_tree(out, c, space);
    }
    for(int i = LEVEL_SPACE; i < space; ++i){
        out << " ";
    }
    out << tree.value << std::endl;
}

template<> 
void print_tree(std::ostream &out, const Tree<Expr::Node> &tree, int space){
    const int LEVEL_SPACE = 12;
    space += LEVEL_SPACE;
    
    if(tree.children.size() > 0)
        print_tree<Expr::Node>(out, tree.children[0], space);
    
    for(int i = LEVEL_SPACE; i < space; ++i){
        out << " ";
    }
    out << tree.value;

    if(tree.children.size() > 1)
        print_tree<Expr::Node>(out, tree.children[1], space);
}

template<typename T> 
void Tree<T>::dbprint(std::ostream &out) {
    print_tree<T>(out, *this, 0);
}

template<>
void Tree<Expr::Node>::dbprint(std::ostream &out) {
    print_tree<Expr::Node>(out, *this, 0);
}

