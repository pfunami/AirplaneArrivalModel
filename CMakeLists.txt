cmake_minimum_required(VERSION 3.12)
project(Program)

set(CMAKE_CXX_STANDARD 17)
set( OpenCV_DIR "/home/denjo/opencv-2.4.9/release" )
set( OpenCV_FOUND 1 )
find_package(GLUT)
find_package(OpenGL)

add_executable(Program main.cpp func.cpp func.h main.h struct.cpp struct.h display.cpp display.h)

target_link_libraries(Program ${GLUT_LIBRARY})
target_link_libraries(Program ${OPENGL_LIBRARY})