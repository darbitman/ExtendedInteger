add_library(DirectedDFS "")
include_directories("../../include/directedDFS"
                    "../../include/digraph"
                    "../../include/bag"
                    "../../include/logger")
target_sources(DirectedDFS PRIVATE
               DirectedDFS.cpp
               "../../include/directedDFS/DirectedDFS.h"
               "../digraph/Digraph.cpp"
               "../../include/digraph/Digraph.h"
               "../../include/bag/Bag.h"
               "../logger/Logger.cpp"
               "../../include/logger/Logger.h")
add_executable(DirectedDFSTest
               DirectedDFSTest.cpp)
target_link_libraries(DirectedDFSTest
                      DirectedDFS)