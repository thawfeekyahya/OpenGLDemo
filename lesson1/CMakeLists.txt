set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SRCS ${SRC_DIR}/*.cpp)
file(GLOB HDRS CONFIGURE_DEPENDS ${HDR_DIR}/.h)


#Get current folder name
get_filename_component(name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_library(${name} ${SRCS})

target_include_directories(${name} PUBLIC ${HDR_DIR})

source_group(TREE ${HDR_DIR} PREFIX "Header Files Intro" FILES ${HDRS})


