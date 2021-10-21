cmake_minimum_required(VERSION 3.8)

# Setup project, languages and standards
project(ebe)
set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(backend)
include_directories(engine)
include_directories(frontend)
include_directories(gp)
include_directories(midend)
include_directories(utils)

# Enable gtest
enable_testing()
add_subdirectory(tests/googletest)

# Create executable
add_executable(
    ${PROJECT_NAME}
    ebe.cpp
    backend/compiler.cpp
    backend/instruction.cpp
    backend/interpreter.cpp
    engine/engine.cpp
    engine/engine_jenn.cpp
    engine/engine_miRANDa.cpp
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

target_link_libraries(
    ${PROJECT_NAME}
    gtest_main
)

# GTest include
include(GoogleTest)

# Docs build
find_package(Doxygen REQUIRED dot)
if(DOXYGEN_FOUND)
    # set input file
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target( docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)