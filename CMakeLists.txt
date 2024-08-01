cmake_minimum_required(VERSION 3.11)

project(OpenGLDemo VERSION 1.0 DESCRIPTION "OpenGL Oreily Tutorial" LANGUAGES CXX)

message("-------------------------------${PROJECT_NAME}----------------------------- \n")

set(CMAKE_BUILD_TYPE "Debug")


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CHAPTERS modules)


foreach(chapter ${CHAPTERS})
	add_subdirectory(${chapter})
endforeach()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Threads REQUIRED)


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
   ${CMAKE_SOURCE_DIR}/libs/build_glfw/src/libglfw3.a
   ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/lib/libGLEW.a
   ${OPENGL_LIBRARIES} 
   ${CMAKE_THREAD_LIBS_INIT}
   ${CMAKE_DL_LIBS}
)  



target_include_directories(${PROJECT_NAME} PUBLIC
   ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/include 
   ${CMAKE_SOURCE_DIR}/libs/glfw/include
   ${OPENGL_INCLUDE_DIRS}  
   ${GLUT_INCLUDE_DIRS}
 )

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${CHAPTERS})


