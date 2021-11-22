/**
 * @file symbol_table.hpp
 * @author Marek Sedlacek
 * @date November 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Symbol table for expression passes
 * 
 * Symbol table holds variables used in pass expressions
 */

#ifndef _SYMBOL_TABLE_HPP_
#define _SYMBOL_TABLE_HPP_

#include <string>
#include "compiler.hpp"
#include "ir.hpp"

/**
 * Namespace for working with variables
 */ 
namespace Vars {
    /**
     * Base class for variables
     */ 
    class Variable {
    public:
        IR::Type type;  ///< Denotes variable's dynamic type
    protected:
        /**
         * Constructor for derived classes to set the type
         * @param Derived class type
         */ 
        Variable(IR::Type type) : type{type} {}
    private:
        friend std::ostream& operator<< (std::ostream &out, Vars::Variable& var);
    public:
        /** 
         * Constructor to create dummy Variable 
         * It's type will be IR::Type::DERIVED  
         */
        Variable() : type{IR::Type::DERIVED} {}
        virtual ~Variable() {}

        /**
         * @defgroup vargetters Variable value extractors
         * Extract values of specified type from a variable
         * @note Since C++ does not allow virtual template functions, then specialized getters have to be used.
         * @return Variable's value
         * @throws EbeSymTableTypeException if incorrect type is requested from deriving class
         * @{
         */ 
        virtual int get_number();
        virtual float get_float();
        virtual std::string get_text();
        /** @} */
        
        /**
         * Formats value in the variable into output stream
         * @param out Output stream to print into
         */ 
        virtual void format_value(std::ostream &out) { out << "$(VALUE)"; }
    };

    /**
     * Variable of type NUMBER
     */ 
    class NumberVar : public Variable {
    private:
        int value;
    public:
        /**
         * Constructor
         * @param value Variable's value
         */ 
        NumberVar(int value) : Variable(IR::Type::NUMBER), value{value} {}

        int get_number() override { return value; }

        void format_value(std::ostream &out) override { out << value; };
    };

    /**
     * Variable of type FLOAT
     */ 
    class FloatVar : public Variable {
    private:
        float value;
    public:
        /**
         * Constructor
         * @param value Variable's value
         */ 
        FloatVar(float value) : Variable(IR::Type::FLOAT), value{value} {}

        float get_float() override { return value; }

        void format_value(std::ostream &out) override { out << value; };
    };

    /**
     * Symbol table is used to hold values of variables in currently interpreted expressions.
     * @note Index 0 is the $ variable (user input).
     */ 
    class SymbolTable : public Compiler {
    private:
        static constexpr int SIZE = 64;  ///< Size of symbol table
        Variable **table;                ///< Symbol table itself
    
        /**
         * Does all needed asserts for set methods and deletes possible previous value
         * @param index Index of set variable
         * @return True if all succeeded
         */ 
        bool assert_set(int index);

        /**
         * Does all needed asserts for get methods
         * @param index Index of set variable
         * @return True if all succeeded
         */ 
        bool assert_get(int index);
    public:
        /**
         * Constructor. Allocates symbol table
         */ 
        SymbolTable();
        
        /**
         * Destructor. Frees up symbol table allocated space.
         */ 
        ~SymbolTable();

        /**
         * Sets variable $index to value in symbol table
         * @param index Variable's index
         * @param value Variable's new value
         * @throw EbeSymTableUnknwonTypeException when not implemented type is used, then error is called
         * @throw EbeSymTableOutOfRangeException when index >= SIZE
         */ 
        template<typename T>
        void set(int index, T value);

        /**
         * Gets value of $index variable in symbol table
         * @param index Variable's index
         * @throw EbeSymTableUnknwonTypeException when not implemented type is used, then error is called
         * @throw EbeSymTableOutOfRangeException when index >= SIZE
         * @return Value of requested variable
         */ 
        template<typename T>
        T get(int index);

        /**
         * Getter for variable type
         * @param index Variable's index
         * @return Variable's dynamic type
         * @throw Same exceptions as get might throw
         */
        IR::Type type_at(int index);
    };
}

#endif//_SYMBOL_TABLE_HPP_