/**
 * @file ebe.hpp
 * @author Marek Sedlacek
 * @date July 2021
 * @copyright Copyright 2021 Marek Sedlacek. All rights reserved.
 * 
 * @brief Entry point of the ebe compiler
 * 
 * Ebe (Edit By Example) compiler can create text editing programs
 * based on example (original program and wanted output on small scale).
 */

#ifndef _EBE_HPP_
#define _EBE_HPP_

#define MACRO_TO_STR_HELPER(x) #x
/** Macro to convert INT macro value into string value */
#define MACRO_TO_STR(x) MACRO_TO_STR_HELPER(x)

#define EBE_VERSION_MAJOR 1  ///< Compiler's major version
#define EBE_VERSION_MINOR 0  ///< Compiler's minor version
#define EBE_VERSION_PATCH 0  ///< Compiler's patch

/** Ebe version as a string */
#define EBE_VERSION MACRO_TO_STR(EBE_VERSION_MAJOR) "." MACRO_TO_STR(EBE_VERSION_MINOR) "." MACRO_TO_STR(EBE_VERSION_PATCH)

#endif//_EBE_HPP_ 
