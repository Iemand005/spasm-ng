cmake_minimum_required(VERSION 3.10)
project(spasm)

file(GLOB SPASM_LIB_SOURCES 
    "src/core/*.c" 
    "src/core/*.cpp"
    "src/core/*.h"
)

set(SPASM_SOURCES 
    "src/main.cpp"
)

set(SPASM_INCLUDES ./)
set(SPASM_CORE_INCLUDES ${CMAKE_SOURCE_DIR}/src/core)

add_library(libspasm STATIC ${SPASM_LIB_SOURCES})
add_executable(spasm ${SPASM_SOURCES})

target_link_libraries(spasm libspasm)

if(MSVC)
    add_compile_options(/TP)
endif()


set_target_properties(libspasm PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(spasm PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(libspasm PUBLIC ${SPASM_INCLUDES})
target_include_directories(spasm PUBLIC ${SPASM_INCLUDES} ${SPASM_CORE_INCLUDES})

add_definitions(-DNO_APPSIGN -DUSE_REUSABLES)