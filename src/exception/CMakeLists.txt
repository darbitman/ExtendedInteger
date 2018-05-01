add_library(Exception "")
include_directories("../../include/exception")
target_sources(Exception
               PRIVATE
               Exception.cpp
               "../../include/exception/Exception.h")
add_executable(ExceptionTest
               ExceptionTest.cpp)
target_link_libraries(ExceptionTest
                      Exception)