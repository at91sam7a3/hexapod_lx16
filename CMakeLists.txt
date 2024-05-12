cmake_minimum_required(VERSION 2.9)

project(hexapod_lx16)

add_subdirectory("${CMAKE_SOURCE_DIR}/lib/lx16lib")
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/hexapod_kinematics")

aux_source_directory(src/ SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(hexapod_lx16 lx16lib hexapod)