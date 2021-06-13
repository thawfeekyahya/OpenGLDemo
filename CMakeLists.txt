cmake_minimum_required(VERSION 3.11)

project(OpenGLDemo VERSION 1.0 DESCRIPTION "OpenGL Oreily Tutorial" LANGUAGES CXX)

message("-------------------------------${PROJECT_NAME}----------------------------- \n")


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

list(APPEND CHAPTERS lesson1)


foreach(chapter ${CHAPTERS})
	add_subdirectory(${chapter})
endforeach()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Threads REQUIRED)



link_libraries(
   ${CMAKE_SOURCE_DIR}/libs/build_glfw/src/libglfw3.a
   ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/build/lib/libGLEW.a
   ${OPENGL_LIBRARIES} 
   ${GLUT_LIBRARY}
   ${CMAKE_THREAD_LIBS_INIT}
   ${CMAKE_DL_LIBS}
)  


include_directories( /usr/local/thyahya/Worksapce/OpenGL/libs/glew-2.1.0/include 
	/usr/local/thyahya/Worksapce/OpenGL/libs/glfw/include
        ${OPENGL_INCLUDE_DIRS}  
        ${GLUT_INCLUDE_DIRS}
 )

message("--------------->> ${CMAKE_SOURCE_DIR}/libs/build_glfw/src/libglfw3.a ")

add_executable(${PROJECT_NAME} main.cpp)


