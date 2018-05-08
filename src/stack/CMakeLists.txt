add_library(Stack "")
include_directories("../../include/stack"
                    "../../include/exception"
                    "../../include/logger")
target_sources(Stack
               PRIVATE
               "../../include/stack/Stack.h"
               "../exception/Exception.cpp"
               "../../include/exception/Exception.h"
               "../logger/Logger.cpp"
               "../../include/logger/Logger.h")
add_executable(StackTest
               StackTest.cpp)
target_include_directories(StackTest PUBLIC "C:/Program Files (x86)/googletest-distribution/include")
target_link_libraries(StackTest
                      Stack)