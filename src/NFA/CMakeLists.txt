add_library(NFA "")
include_directories("../../include/NFA"
                    "../../include/digraph"
                    "../../include/stack"
                    "../../include/bag"
                    "../../include/directedDFS"
                    "../../include/exception")
set(NFA_Sources
    NFA.cpp
    "../digraph/Digraph.cpp"
    "../directedDFS/DirectedDFS.cpp"
    "../exception/Exception.cpp"
    "../../include/exception/Exception.h"
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
                      Digraph
                      DirectedDFS
                      Exception)