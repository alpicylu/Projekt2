cmake_minimum_required(VERSION 3.10)

project(Projekt_2)

#with this line we can add all .cpp files to SOURCE without expicitly listing them
aux_source_directory(src/ SRC)

set(SOURCES ${SRC})

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC inc/)