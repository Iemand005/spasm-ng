cmake_minimum_required(VERSION 3.10)
project(spasm)

# add_subdirectory(external/openssl-cmake)

file(GLOB_RECURSE SPASM_SOURCES 
    external/md5-c/md5.c
    "*.c" 
    "*.cpp"
    "*.h"
    "*.hpp"
)

set(SPASM_INCLUDES ./ external/md5-c)

add_library(libspasm STATIC ${SPASM_SOURCES})
add_executable(spasm ${SPASM_SOURCES})

set_target_properties(libspasm PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(libspasm PUBLIC ${SPASM_INCLUDES})
target_include_directories(spasm PUBLIC ${SPASM_INCLUDES})

add_definitions(-DNO_APPSIGN)