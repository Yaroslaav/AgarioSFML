cmake_minimum_required(VERSION 3.26)
project(AgarioProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

add_subdirectory(external/SFML)
add_subdirectory(Engine)
add_subdirectory(Agario)