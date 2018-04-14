add_library(Exception "")
include_directories("../../include/exception")
set(Exception_Sources
    Exception.cpp
    "../../include/exception/Exception.h")
target_sources(Exception PRIVATE
               ${Exception_Sources})