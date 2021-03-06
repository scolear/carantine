cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

project(carantine_project)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} "main.cpp"
    "movement/sensors/ultrasonicsensor.cpp"
    "movement/sensors/trisonarhandler.cpp"
    "movement/motors/motor.cpp"
    "movement/motors/motordriver.cpp"
    )

find_library(wiringPi_LIB wiringPi)
target_link_libraries(${PROJECT_NAME} ${wiringPi_LIB})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} Threads::Threads)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
