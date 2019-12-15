cmake_minimum_required(VERSION 3.8)
project(tree-cpp17 VERSION 0.1.0)

set(CREDITS "Tan Li Boon")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ASCII_ONLY "Print only ASCII characters (Disables UTF-8 output)" OFF)

string(TIMESTAMP CURRENT_YEAR "%Y")
configure_file(
	"${CMAKE_SOURCE_DIR}/config.hpp.in"
	"${CMAKE_SOURCE_DIR}/config.hpp"
)

add_executable(tree ${CMAKE_SOURCE_DIR}/tree.cpp ${CMAKE_SOURCE_DIR}/config.hpp ${CMAKE_SOURCE_DIR}/platform.cpp)
target_compile_definitions(tree PRIVATE ASCII_ONLY=$<BOOL:${ASCII_ONLY}>)

install(TARGETS tree DESTINATION bin)
