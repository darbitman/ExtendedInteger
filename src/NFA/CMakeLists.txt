add_library(NFA "")
include_directories("../../include/NFA"
                    "../../include/digraph"
                    "../../include/stack"
                    "../../include/bag")
target_sources(NFA PRIVATE
               NFA.cpp
               "../digraph/Digraph.cpp"
               "../stack/Stack.cpp"
               "../../include/NFA/NFA.h"
               "../../include/digraph/Digraph.h"
               "../../include/stack/Stack.h"
               "../../include/bag/Bag.h")
add_executable(NFATest
               NFATest.cpp
               NFA.cpp
               "../../include/NFA/NFA.h"
               "../../include/bag/Bag.h")
target_link_libraries(NFATest
                      NFA
                      Stack
                      Digraph)