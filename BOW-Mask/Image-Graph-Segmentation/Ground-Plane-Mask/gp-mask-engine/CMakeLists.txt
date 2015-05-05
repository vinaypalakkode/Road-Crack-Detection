cmake_minimum_required (VERSION 2.6)
project(ground-plane-mask)
find_package( OpenCV REQUIRED)
include_directories(include)
add_executable( gp-mask segment.cpp)
target_link_libraries(gp-mask ${OpenCV_LIBS} )


