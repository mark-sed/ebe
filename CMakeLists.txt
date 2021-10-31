cmake_minimum_required(VERSION 3.8)

# Setup project, languages and standards
project(ebe)
set(CMAKE_CXX_STANDARD 17)

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
    engine/engine.cpp
    engine/engine_jenn.cpp
    engine/engine_miRANDa.cpp
    frontend/lexer_text.cpp
    frontend/parser_text.cpp
    frontend/scanner_text.cpp
    frontend/lexer_ebel.cpp
    frontend/parser_ebel.cpp
    frontend/scanner_ebel.cpp
    frontend/preprocessor.cpp
    frontend/scanner.cpp
    gp/gp.cpp
    midend/ir.cpp
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

# TODO:
# bison -d frontend/grammars/parser_text.yy -o frontend/parser_text.cpp
# flex --outfile=frontend/lexer_text.cpp --header-file=frontend/lexer_text.hpp frontend/grammars/lexer_text.ll