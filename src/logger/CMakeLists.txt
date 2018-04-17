add_library(Logger "")
include_directories("../../include/logger")
set(Logger_Sources Logger.cpp
                   "../../include/logger/logger.h")
target_sources(Logger PRIVATE
               ${Logger_Sources})