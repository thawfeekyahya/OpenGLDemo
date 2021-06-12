cmake_minimum_required(VERSION 3.11)

project(OpenGLDemo VERSION 1.0 DESCRIPTION "OpenGL Oreily Tutorial" LANGUAGES CXX)

message("-------------------------------${PROJECT_NAME}----------------------------- \n")


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

list(APPEND CHAPTERS lesson1)


foreach(chapter ${CHAPTERS})
	add_subdirectory(${chapter})
endforeach()


include_directories( /usr/local/thyahya/Worksapce/OpenGL/libs/glew-2.1.0/include 
	/usr/local/thyahya/Worksapce/OpenGL/libs/glfw/include )

add_executable(${PROJECT_NAME} main.cpp 
	${CMAKE_SOURCE_DIR}/libs/build_glfw/src/libglfw3.a 
        ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/build/lib/libGLEW.a)

target_link_libraries(${PROJECT_NAME} ${CHAPTERS})  
