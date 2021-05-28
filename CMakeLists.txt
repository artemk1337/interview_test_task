cmake_minimum_required(VERSION 3.19)

project( test_task )
add_executable( test_task main.cpp main.h )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( test_task ${OpenCV_LIBS} )
