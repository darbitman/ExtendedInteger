add_library(NFA "")
include_directories("../../include/NFA"
                    "../../include/digraph"
                    "../../include/stack"
                    "../../include/bag"
                    "../../include/directedDFS")
set(NFA_Sources
    NFA.cpp
    "../digraph/Digraph.cpp"
    "../stack/Stack.cpp"
    "../directedDFS/DirectedDFS.cpp"
    "../../include/directedDFS/DirectedDFS.h"
    "../../include/NFA/NFA.h"
    "../../include/digraph/Digraph.h"
    "../../include/stack/Stack.h"
    "../../include/bag/Bag.h")
    
target_sources(NFA PRIVATE
               ${NFA_Sources})

add_executable(NFATest
               NFATest.cpp
               ${NFA_Sources})
target_link_libraries(NFATest
                      NFA
                      Stack
                      Digraph
                      DirectedDFS)