cmake_minimum_required(VERSION 3.11)

project(OpenGLDemo VERSION 1.0 DESCRIPTION "OpenGL Oreily Tutorial" LANGUAGES CXX)

message("-------------------------------${PROJECT_NAME}----------------------------- \n")


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

list(APPEND CHAPTERS lesson1)


foreach(chapter ${CHAPTERS})
	add_subdirectory(${chapter})
endforeach()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${CHAPTERS})  
