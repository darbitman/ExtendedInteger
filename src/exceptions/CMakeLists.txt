add_library(Exceptions "")
include_directories("../../include/exceptions")
set(Exceptions_Sources
    Exceptions.cpp
    "../../include/exceptions/Exceptions.h")
    
target_sources(Exceptions PRIVATE
               ${Exceptions_Sources})

#add_executable(NFATest
#               NFATest.cpp
#               ${NFA_Sources})
#target_link_libraries(NFATest
#                      NFA
#                      Digraph
#                      DirectedDFS)