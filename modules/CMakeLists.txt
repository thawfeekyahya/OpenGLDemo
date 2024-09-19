set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SRCS ${SRC_DIR}/*.cpp)
file(GLOB HDRS CONFIGURE_DEPENDS ${HDR_DIR}/.h)


#Get current folder name
get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_library(${name} ${SRCS})

find_package(OpenGL REQUIRED)

target_include_directories(${name} PUBLIC ${HDR_DIR}
        ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/include 
	${CMAKE_SOURCE_DIR}/libs/glfw/include
	${CMAKE_SOURCE_DIR}/libs/glm_lib
   	${CMAKE_SOURCE_DIR}/libs/stb_img
        ${OPENGL_INCLUDE_DIRS}  
        ${GLUT_INCLUDE_DIRS}
)

target_link_libraries(${name}
   ${CMAKE_SOURCE_DIR}/libs/build_glfw/src/libglfw3.a
   ${CMAKE_SOURCE_DIR}/libs/glew-2.1.0/lib/libGLEW.a
   ${OPENGL_LIBRARIES} 
   ${CMAKE_THREAD_LIBS_INIT}
   ${CMAKE_DL_LIBS}
)  


add_custom_command(
        TARGET ${name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/shader_programs
                ${CMAKE_BINARY_DIR}
)

source_group(TREE ${HDR_DIR} PREFIX "Header Files Intro" FILES ${HDRS})


