cmake_minimum_required(VERSION 3.10)
project(DiseaseSimulator)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Weffc++ -pedantic-errors -Wno-unused-parameter -Wshadow-compatible-local)
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")
add_executable(DiseaseSimulator  ${SOURCE_FILES})
