add_library(DirectedDFS "")
include_directories("../../include/directedDFS"
                    "../../include/digraph"
                    "../../include/stack"
                    "../../include/bag")
target_sources(DirectedDFS PRIVATE
               DirectedDFS.cpp
               "../digraph/Digraph.cpp"
               "../stack/Stack.cpp"
               "../../include/directedDFS/DirectedDFS.h"
               "../../include/digraph/Digraph.h"
               "../../include/stack/Stack.h"
               "../../include/bag/Bag.h")
#add_executable(NFATest
#               NFATest.cpp
#               NFA.cpp
#               "../../include/NFA/NFA.h"
#               "../../include/bag/Bag.h")
#target_link_libraries(NFATest
#                      NFA
#                      Stack
#                      Digraph)