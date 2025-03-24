cmake_minimum_required(VERSION 3.10)
project(simplesynth)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(program_synthesis
   src/expression.cpp
   src/synthesizer.cpp
)

target_link_libraries(program_synthesis PRIVATE spdlog::spdlog)

add_subdirectory(examples)
