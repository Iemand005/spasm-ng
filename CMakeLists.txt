cmake_minimum_required(VERSION 3.10)
project(spasm)

file(GLOB_RECURSE SPASM_SOURCES 
    "*.c" 
    "*.cpp"
    "*.h"
    "*.hpp"
)

add_library(spasm STATIC ${SPASM_SOURCES})

target_include_directories(spasm PUBLIC external/openssl/include)

target_include_directories(spasm PUBLIC ./)

set_target_properties(spasm PROPERTIES LINKER_LANGUAGE CXX)