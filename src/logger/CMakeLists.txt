add_library(Logger "")
include_directories("../../include/logger")
set(Logger_Sources Logger.cpp
                   "../../include/logger/Logger.h")
target_sources(Logger PRIVATE
               ${Logger_Sources})
add_executable(LoggerTest
               LoggerTest.cpp)
target_link_libraries(LoggerTest
                      Logger)