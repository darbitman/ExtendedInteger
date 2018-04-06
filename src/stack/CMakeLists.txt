add_library(Stack "")
include_directories("../../include/Stack")
target_sources(Stack PRIVATE
               Stack.cpp
               "../../include/Stack/Stack.h")
add_executable(StackTest
               StackTest.cpp
               Stack.cpp
               "../../include/Stack/Stack.h")
target_link_libraries(StackTest Stack)