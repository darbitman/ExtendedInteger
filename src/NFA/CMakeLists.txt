add_library(NFA "")
include_directories("../../include/NFA"
                    "../../include/digraph"
                    "../../include/stack"
                    "../../include/bag"
                    "../../include/directedDFS"
                    "../../include/exception"
                    "../../include/logger")
set(NFA_Sources
    NFA.cpp
    "../../include/NFA/NFA.h")
target_sources(NFA PRIVATE
               ${NFA_Sources}
               "../digraph/Digraph.cpp"
               "../../include/digraph/Digraph.h"
               "../../include/stack/Stack.h"
               "../../include/bag/Bag.h"
               "../directedDFS/DirectedDFS.cpp"
               "../../include/directedDFS/DirectedDFS.h"
               "../exception/Exception.cpp"
               "../../include/exception/Exception.h"
               "../logger/Logger.cpp"
               "../../include/logger/Logger.h")
add_executable(NFATest
               NFATest.cpp)
target_link_libraries(NFATest
                      NFA)