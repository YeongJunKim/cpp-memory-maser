cmake_minimum_required(VERSION 3.5)

project (cpp_memory_master)

add_compile_options(-std=c++17)

find_package(Threads)


add_subdirectory(owner_pointer)
add_subdirectory(shared_pointer)
add_subdirectory(unique_pointer)
add_subdirectory(example)
