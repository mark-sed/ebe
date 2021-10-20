cmake_minimum_required(VERSION 3.8)
set(pname ebe)

# Setup project, languages and standards
project(${pname})
set(CMAKE_CXX_STANDARD 17)

# Enable gtest
enable_testing()
add_subdirectory(tests/googletest)

# TODO: After stable release change this to explicit listing
# Source files
file(GLOB SRCS_BACKEND backend/*.cpp)
file(GLOB SRCS_ENGINE engine/*.cpp)
file(GLOB SRCS_FRONTEND frontend/*.cpp)
file(GLOB SRCS_GP gp/*.cpp)
file(GLOB SRCS_MIDEND midend/*.cpp)
file(GLOB SRCS_UTILS utils/*.cpp)

# Headers
file(GLOB HDRS_BACKEND backend/*.hpp)
file(GLOB HDRS_ENGINE engine/*.hpp)
file(GLOB HDRS_FRONTEND frontend/*.hpp)
file(GLOB HDRS_GP gp/*.hpp)
file(GLOB HDRS_MIDEND midend/*.hpp)
file(GLOB HDRS_UTILS utils/*.hpp)

# Create executable
add_executable(
    ${panme}
    ebe.cpp
    backend/compiler.cpp
    backend/instruction.cpp
    backend/interpreter.cpp
    ebe.cpp
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
    ${panme}
    gtest_main
)

# GTest include
include(GoogleTest)