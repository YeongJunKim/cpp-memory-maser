cmake_minimum_required(VERSION 3.5)

project(opencv_example)

set(OpenCV_DIR [OpenCV.cmake PATH])

find_package(OpenCV REQUIRED)

add_compile_options(-std=c++17)

include_directories(${OpenCV_INCLUDE_DIR})

add_executable(unique_main unique_main)
target_link_libraries(unique_main ${OpenCV_LIBRARIES})

add_executable(shared_main shared_main)
target_link_libraries(shared_main ${OpenCV_LIBRARIES})