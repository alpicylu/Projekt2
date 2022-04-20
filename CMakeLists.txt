cmake_minimum_required(VERSION 3.10)

project(Projekt_2)

set(SOURCES src/main.cpp src/read_csv.cpp inc/DLL.hh inc/packet.hh inc/read_csv.hh)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC inc/ src/)