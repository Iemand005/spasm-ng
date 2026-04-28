file(GLOB_RECURSE SPASM_SOURCES 
    "*.c" 
    "*.cpp"
    "*.h"
    "*.hpp"
)

add_library(spasm STATIC ${SPASM_SOURCES})

target_include_directories(spasm PUBLIC ./)

set_target_properties(spasm PROPERTIES LINKER_LANGUAGE CXX)