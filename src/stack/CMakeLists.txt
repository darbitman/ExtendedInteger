include_directories("../../include/stack"
                    "../../include/exception")
add_executable(StackTest
               StackTest.cpp
               "../exception/Exception.cpp"
               "../../include/stack/Stack.h"
               "../../include/exception/Exception.h")
target_link_libraries(StackTest Exception)