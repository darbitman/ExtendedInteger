cmake_minimum_required(VERSION 3.0)
project(ExtendedInteger)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(LOGGER_VERBOSITY 0)
add_definitions(-DLOGGER_VERBOSITY=${LOGGER_VERBOSITY})
add_subdirectory("src")

#add_library(merged STATIC dummy.cpp)
#set_target_properties(merged PROPERTIES STATIC_LIBRARY_FLAGS "${CMAKE_BINARY_DIR}/Debug/UnsignedExtendedInt.lib ${CMAKE_BINARY_DIR}/Debug/ExtendedInt.lib")




#install(FILES "${LIBRARY_OUTPUT_PATH}/Debug/ExtendedInteger.lib" DESTINATION lib)
install(FILES "include/extendedInt/ExtendedInt.h"
              "include/extendedInt/ExtendedInteger.h"
              "include/extendedInt/SignedExtendedInt.h"
              "include/extendedInt/UnsignedExtendedInt.h"
              "include/bag/Bag.h"
              "include/digraph/Digraph.h"
              "include/directedDFS/DirectedDFS.h"
              "include/exception/Exception.h"
              "include/logger/Logger.h"
              "include/NFA/NFA.h"
              "include/stack/Stack.h"
              DESTINATION include)
install(FILES "${CMAKE_BINARY_DIR}/ExtendedInteger-config.cmake" DESTINATION lib/cmake/ExtendedInteger)

