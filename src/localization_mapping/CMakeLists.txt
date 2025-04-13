cmake_minimum_required(VERSION 3.8)
project(ig_lio_c)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -O3)
add_compile_definitions(SOPHUS_USE_BASIC_LOGGING)
set(CMAKE_BUILD_TYPE Release)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake_modules)
































