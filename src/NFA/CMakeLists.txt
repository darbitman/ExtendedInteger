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
               ${NFA_Sources})
add_executable(NFATest
               NFATest.cpp)
target_link_libraries(NFATest
                      NFA
                      Digraph
                      DirectedDFS
                      Exception
                      Logger)
target_link_libraries(NFA
                      Digraph
                      DirectedDFS
                      Exception
                      Logger)