add_library(DirectedDFS "")
include_directories("../../include/directedDFS"
                    "../../include/digraph"
                    "../../include/bag")
target_sources(DirectedDFS PRIVATE
               DirectedDFS.cpp
               "../digraph/Digraph.cpp"
               "../stack/Stack.cpp"
               "../../include/directedDFS/DirectedDFS.h"
               "../../include/digraph/Digraph.h"
               "../../include/bag/Bag.h")
add_executable(DirectedDFSTest
               DirectedDFSTest.cpp
               DirectedDFS.cpp
               "../digraph/Digraph.cpp"
               "../../include/directedDFS/DirectedDFS.h"
               "../../include/digraph/Digraph.h"
               "../../include/bag/Bag.h")
target_link_libraries(DirectedDFSTest DirectedDFS)