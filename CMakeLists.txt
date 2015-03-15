PROJECT(simpleClientForEndoScout_OSX)

cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/build/bin")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_HOME_DIRECTORY}/build/bin")

file(GLOB headers 
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
  )

# --------------------------------------------------------------------------
# Sources
set(SOURCE_FILES
  simpleClientForEndoScout_OSX.c
)

# --------------------------------------------------------------------------
# Build and install the library

ADD_EXECUTABLE(
  simpleClientForEndoScout_OSX ${SOURCE_FILES} 
  )

target_link_libraries(
  simpleClientForEndoScout_OSX
  # You don't need -lsocket on OS X
  #socket
  )

