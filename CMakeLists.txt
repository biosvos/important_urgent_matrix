cmake_minimum_required(VERSION 3.23)
project(important_urgent_matrix)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
enable_testing()
include(GoogleTest)

add_subdirectory(domain)
add_subdirectory(usecase)
add_subdirectory(infra)

add_executable(app main.cpp)
target_link_libraries(app ftx usecase file_sequence)
