cmake_minimum_required(VERSION 3.10)
project(spasm)

# add_subdirectory(external/openssl-cmake)

file(GLOB_RECURSE SPASM_SOURCES 
    "*.c" 
    "*.cpp"
    "*.h"
    "*.hpp"
)

add_library(spasm STATIC ${SPASM_SOURCES})

if(MSVC)
    # target_compile_options(spasm PRIVATE "/showIncludes")
endif()

target_include_directories(spasm PUBLIC ./)

# target_link_libraries(spasm OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(spasm PRIVATE crypto)

set_target_properties(spasm PROPERTIES LINKER_LANGUAGE CXX)

add_definitions(-DARCH_X86_64 -D__x86_64__)