add_library(Stack "")
include_directories("../../include/stack")
target_sources(Stack PRIVATE
               Stack.cpp
               "../../include/stack/Stack.h")
add_executable(StackTest
               StackTest.cpp
               Stack.cpp
               "../../include/stack/Stack.h")
target_link_libraries(StackTest Stack)