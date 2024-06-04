cmake_minimum_required(VERSION 3.0)
project(hexapod_lx16)

include(/home/oleksii/cmake-test/PI.cmake)

      set(CMAKE_THREAD_LIBS_INIT "-lpthread")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
      set(CMAKE_HAVE_THREADS_LIBRARY 1)
      set(CMAKE_USE_WIN32_THREADS_INIT 0)
      set(CMAKE_USE_PTHREADS_INIT 1)
      set(THREADS_PREFER_PTHREAD_FLAG ON)

add_subdirectory("${CMAKE_SOURCE_DIR}../lx16lib")
add_subdirectory("${CMAKE_SOURCE_DIR}../hexapod_kinematics")

aux_source_directory(src/ SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(hexapod_lx16 lx16lib hexapod wiringPi)