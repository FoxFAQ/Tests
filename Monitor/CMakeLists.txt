cmake_minimum_required(VERSION 2.8)

project(Monitor)
set (SOURCES sensor.cpp monitor.cpp main.cpp monitor.h sensor.h)
add_executable(${PROJECT_NAME} ${SOURCES})
