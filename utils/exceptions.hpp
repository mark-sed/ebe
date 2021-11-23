/**
 * @file exceptions.hpp
 * @author Marek Sedlacek
 * @date October 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Compiler exceptions mainly for util functions
 * 
 * Compiler exceptions mainly for util functions
 */

#ifndef _EXCEPTIONS_HPP_
#define _EXCEPTIONS_HPP_

#include <exception>
#include <string>

/**
 * Exception namespace
 */ 
namespace Exception {
    /**
     * Base Exception class
     * Is supposed to be extended by specific exceptions
     */ 
    class EbeException : public std::exception {
    protected:
        std::string msg;       ///< Message containing exception description
        const char *type;
        
        /**
         * Constructor
         * @param msg C style string with the error message
         * @param type Children class exception type
         */ 
        EbeException(const char *msg, const char *type) : msg(msg), type(type) {}

        /**
         * Constructor
         * @param msg string with the error message
         * @param type Children class exception type
         */ 
        EbeException(std::string msg, const char *type) : msg(msg), type(type) {}

    public:
        /// Virtual destructor for children classes
        virtual ~EbeException() noexcept {}

        /**
         * Returns exception type 
         */ 
        const char *get_type() const noexcept {
            return this->type;
        }

        /**
         * Returns error message
         * Mainly here for case that exception is not handeled
         * @return Error message
         */ 
        virtual const char *what() const noexcept {
            return msg.c_str();
        }
    };


    /**
     * Exception for when there's problem with data types
     * such as casting
     */
    class EbeTypeException : public EbeException {
    private:
        static constexpr const char *TYPE = "Type exception";
    public:
        /**
         * Constructor
         * @param msg C style string with the error message
         */ 
        EbeTypeException(const char *msg) : EbeException(msg, TYPE) {}

        /**
         * Constructor
         * @param msg string with the error message
         */ 
        EbeTypeException(std::string msg) : EbeException(msg, TYPE) {}
    };


    /**
     * Exception for when there's problem with data types
     * of variables in symbol table
     */
    class EbeSymTableTypeException : public EbeException {
    private:
        static constexpr const char *TYPE = "Symbol table type exception";
    public:
        /**
         * Constructor
         * @param msg C style string with the error message
         */ 
        EbeSymTableTypeException(const char *msg) : EbeException(msg, TYPE) {}

        /**
         * Constructor
         * @param msg string with the error message
         */ 
        EbeSymTableTypeException(std::string msg) : EbeException(msg, TYPE) {}
    };

    /**
     * Exception for when the variable index is out of range
     */
    class EbeSymTableOutOfRangeException : public EbeException {
    private:
        static constexpr const char *TYPE = "Symbol table out of range exception";
    public:
        /**
         * Constructor
         * @param msg C style string with the error message
         */ 
        EbeSymTableOutOfRangeException(const char *msg) : EbeException(msg, TYPE) {}

        /**
         * Constructor
         * @param msg string with the error message
         */ 
        EbeSymTableOutOfRangeException(std::string msg) : EbeException(msg, TYPE) {}
    };
    
    /**
     * Exception for when the compiler requests type that the symbol table cannot hold
     */
    class EbeSymTableUnknwonTypeException : public EbeException {
    private:
        static constexpr const char *TYPE = "Symbol table out of range exception";
    public:
        /**
         * Constructor
         * @param msg C style string with the error message
         */ 
        EbeSymTableUnknwonTypeException(const char *msg) : EbeException(msg, TYPE) {}

        /**
         * Constructor
         * @param msg string with the error message
         */ 
        EbeSymTableUnknwonTypeException(std::string msg) : EbeException(msg, TYPE) {}
    };

    /**
     * Exception for when the compiler requests variable that was not yet defined
     */
    class EbeSymTableUndefinedVarException : public EbeException {
    private:
        static constexpr const char *TYPE = "Symbol table out of range exception";
    public:
        /**
         * Constructor
         * @param msg C style string with the error message
         */ 
        EbeSymTableUndefinedVarException(const char *msg) : EbeException(msg, TYPE) {}

        /**
         * Constructor
         * @param msg string with the error message
         */ 
        EbeSymTableUndefinedVarException(std::string msg) : EbeException(msg, TYPE) {}
    };

    /**
     * Exception for division by zero
     */
    class EbeDivisionByZeroException : public EbeException {
    private:
        static constexpr const char *TYPE = "Division by zero exception";
    public:
        /**
         * Constructor
         * @param msg C style string with the error message
         */ 
        EbeDivisionByZeroException(const char *msg) : EbeException(msg, TYPE) {}

        /**
         * Constructor
         * @param msg string with the error message
         */ 
        EbeDivisionByZeroException(std::string msg) : EbeException(msg, TYPE) {}
    };
}

#endif//_EXCEPTIONS_HPP_
