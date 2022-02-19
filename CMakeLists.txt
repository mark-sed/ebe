cmake_minimum_required(VERSION 3.8)

# Setup project, languages and standards
project(ebe)
set(CMAKE_CXX_STANDARD 17)

# TODO: Possibly always request the type to be specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g")

# Includes for headers
include_directories(.)
include_directories(backend)
include_directories(engine)
include_directories(frontend)
include_directories(gp)
include_directories(midend)
include_directories(utils)

# Source files excluding main
set(SOURCES 
    backend/compiler.cpp
    backend/instruction.cpp
    backend/interpreter.cpp
    backend/symbol_table.cpp
    engine/engine.cpp
    engine/engine_jenn.cpp
    engine/engine_miRANDa.cpp
    engine/fitness.cpp
    frontend/lexer_text.cpp
    frontend/parser_text.cpp
    frontend/scanner_text.cpp
    frontend/lexer_ebel.cpp
    frontend/parser_ebel.cpp
    frontend/scanner_ebel.cpp
    frontend/pragmas.cpp
    frontend/preprocessor.cpp
    frontend/scanner.cpp
    gp/gp.cpp
    midend/ir.cpp
    midend/tree.cpp
    midend/expression.cpp
    utils/arg_parser.cpp
    utils/exceptions.cpp
    utils/logging.cpp
    utils/rng.cpp
    utils/utils.cpp
)

# Test source files
set(TEST_SRCS
    tests/test_utils.cpp
    tests/test_interpreter.cpp
    tests/test_scanner.cpp
    tests/test_argparse.cpp
)

# Enable gtest
enable_testing()
add_subdirectory(tests/googletest)

# Targets
# ebe target
add_executable(
    ${PROJECT_NAME}
    ebe.cpp
    ${SOURCES}
)
target_link_libraries(${PROJECT_NAME} m)

# ebetests target
add_executable(
    ebetests
    ${TEST_SRCS}
    ${SOURCES}
)

target_link_libraries(
    ebetests
    gtest_main
)

# GTest include
include(GoogleTest)
gtest_discover_tests(ebetests)

# Docs build
# docs target
find_package(Doxygen REQUIRED dot)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target( docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# Rebuilding lexer and parser when files don't exist and flex and bison are present
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
if(BISON_FOUND)
    if(FLEX_FOUND)
        bison_target(parser_text ${CMAKE_CURRENT_SOURCE_DIR}/frontend/grammars/parser_text.yy ${CMAKE_CURRENT_SOURCE_DIR}/frontend/parser_text.cpp)
        flex_target(lexer_text ${CMAKE_CURRENT_SOURCE_DIR}/frontend/grammars/lexer_text.ll ${CMAKE_CURRENT_SOURCE_DIR}/frontend/lexer_text.cpp COMPILE_FLAGS "--header-file=frontend/lexer_text.hpp")
        ADD_FLEX_BISON_DEPENDENCY(lexer_text parser_text)
        bison_target(parser_ebel ${CMAKE_CURRENT_SOURCE_DIR}/frontend/grammars/parser_ebel.yy ${CMAKE_CURRENT_SOURCE_DIR}/frontend/parser_ebel.cpp COMPILE_FLAGS "-p ee")
        flex_target(lexer_ebel ${CMAKE_CURRENT_SOURCE_DIR}/frontend/grammars/lexer_ebel.ll ${CMAKE_CURRENT_SOURCE_DIR}/frontend/lexer_ebel.cpp COMPILE_FLAGS "-P ee --header-file=frontend/lexer_ebel.hpp")
        ADD_FLEX_BISON_DEPENDENCY(lexer_ebel parser_ebel)
    endif(FLEX_FOUND)
endif (BISON_FOUND)

# Copy ebe to /usr/bin to use as a command
#if(UNIX) 
#    add_custom_command(
#            TARGET ebe
#            POST_BUILD
#            COMMAND sudo cp $<TARGET_FILE:ebe> "/usr/bin"
#            COMMENT "Copying ebe binary to /usr/bin"
#    )
#endif(UNIX)
