add_library(NFA "")
include_directories("../../include/NFA"
                    "../../include/digraph"
                    "../../include/stack")
target_sources(NFA PRIVATE
               NFA.cpp
               "../digraph/Digraph.cpp"
               "../stack/Stack.cpp"
               "../../include/NFA/NFA.h"
               "../../include/digraph/Digraph.h"
               "../../include/stack/Stack.h")
add_executable(NFATest
               NFATest.cpp
               NFA.cpp
               "../../include/NFA/NFA.h")
target_link_libraries(NFATest
                      NFA
                      Stack
                      Digraph)