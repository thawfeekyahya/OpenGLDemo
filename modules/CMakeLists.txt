set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SRCS ${SRC_DIR}/*.cpp)
file(GLOB HDRS CONFIGURE_DEPENDS ${HDR_DIR}/.h)


#Get current folder name
get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_library(${name} ${SRCS})

find_package(OpenGL REQUIRED)


target_include_directories(${name} PUBLIC 
	${HDR_DIR}
	${COMMON_INCLUDES}
        ${GLUT_INCLUDE_DIRS}
)

target_link_libraries(${name}
   ${COMMON_LIBS}
   ${CMAKE_THREAD_LIBS_INIT}
)  


add_custom_command(
        TARGET ${name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/shader_programs
                ${CMAKE_BINARY_DIR}
)

source_group(TREE ${HDR_DIR} PREFIX "Header Files Intro" FILES ${HDRS})


