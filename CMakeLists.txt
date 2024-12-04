cmake_minimum_required(VERSION 3.11)

project(OpenGLDemo VERSION 1.0 DESCRIPTION "OpenGL Antons Tutorial" LANGUAGES CXX)

message("-------------------------------${PROJECT_NAME}----------------------------- \n")

set(CMAKE_BUILD_TYPE "Debug")


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CHAPTERS modules)


find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)


file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})


# Check if we're on macOS
if(APPLE)

    set(CMAKE_OSX_ARCHITECTURES "arm64")


    set(COMMON_INCLUDES 
        ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/include 
	${CMAKE_SOURCE_DIR}/libs/glfw_34_mac/include
        ${CMAKE_SOURCE_DIR}/libs/glm_lib
        ${CMAKE_SOURCE_DIR}/libs/stb_img
        ${OPENGL_INCLUDE_DIRS}  
     )

    # Link Cocoa framework to your target
      set(COMMON_LIBS
	"-framework Metal"               # Metal framework
        "-framework OpenGL"              # OpenGL framework
	"-framework IOKit"               # IOKit framework
	"-framework CoreFoundation"      # CoreFoundation framework
	"-framework AppKit"      
	"-framework CoreGraphics"
	"-framework Cocoa"               # Cocoa framework (important for macOS)

        ${CMAKE_SOURCE_DIR}/libs/glfw_34_mac/lib-arm64/libglfw3.a
	${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/lib/libGLEW.a  # GLEW static library
	${OPENGL_LIBRARIES}              # OpenGL libraries
	${CMAKE_DL_LIBS}                # DL libraries (e.g., dynamic loading)
      )
elseif(UNIX)
 set(COMMON_INCLUDES
           ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/include 
           ${CMAKE_SOURCE_DIR}/libs/glfw/include
           ${CMAKE_SOURCE_DIR}/libs/glm_lib
           ${CMAKE_SOURCE_DIR}/libs/stb_img
           ${OPENGL_INCLUDE_DIRS}  
         )
 

 set(COMMON_LIBS
	   ${CMAKE_SOURCE_DIR}/libs/build_glfw/src/libglfw3.a
           ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/lib/libGLEW.a
           ${OPENGL_LIBRARIES} 
           ${CMAKE_DL_LIBS}
	 )
endif()


foreach(chapter ${CHAPTERS})
	add_subdirectory(${chapter})
endforeach()


target_include_directories(${PROJECT_NAME} PRIVATE ${COMMON_INCLUDES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${COMMON_LIBS} ${CHAPTERS})
