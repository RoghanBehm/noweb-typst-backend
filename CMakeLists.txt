cmake_minimum_required(VERSION 3.16)

project(noweb_typst LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(core STATIC
    src/emitter.cpp
    src/main.cpp
    src/parser.cpp
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(noweb_typst
    src/main.cpp
)

target_link_libraries(noweb_typst
    PRIVATE core
)
