cmake_minimum_required(VERSION 3.10)
project(spasm)

# add_subdirectory(external/openssl-cmake)

file(GLOB SPASM_SOURCES 
    # external/md5-c/md5.c
    "src/*.c" 
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
)

set(SPASM_INCLUDES ./)

add_library(libspasm STATIC ${SPASM_SOURCES})
add_executable(spasm ${SPASM_SOURCES})

if(MSVC)
    add_compile_options(/TP)
endif()


set_target_properties(libspasm PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(spasm PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(libspasm PUBLIC ${SPASM_INCLUDES})
target_include_directories(spasm PUBLIC ${SPASM_INCLUDES})

add_definitions(-DNO_APPSIGN -DUSE_REUSABLES)