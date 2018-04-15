add_library(Exception "")
include_directories("../../include/exception")
set(Exception_Sources
    Exception.cpp
    "../../include/exception/Exception.h")
target_sources(Exception PRIVATE
               ${Exception_Sources})
add_executable(ExceptionTest
               ExceptionTest.cpp
               ${Exception_Sources})
target_link_libraries(ExceptionTest
                      Exception)