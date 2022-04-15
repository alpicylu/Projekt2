cmake_minimum_required(VERSION 3.10)

project(Projekt_2)

set(SOURCES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC inc/ src/)