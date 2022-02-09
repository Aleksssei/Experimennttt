cmake_minimum_required(VERSION 3.21)
project(new_c_projects C)

set(CMAKE_C_STANDARD 11)

add_executable(new_c_projects main.c)
add_subdirectory(libs)
target_link_libraries(new_c_projects data_structures)
target_link_libraries(new_c_projects algorithms)
