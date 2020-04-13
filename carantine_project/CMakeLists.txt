cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

project(carantine_project)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} "main.cpp" "movement/ultrasonicsensor.cpp" "movement/trisonarhandler.cpp")

find_library(wiringPi_LIB wiringPi)
target_link_libraries(${PROJECT_NAME} ${wiringPi_LIB})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
