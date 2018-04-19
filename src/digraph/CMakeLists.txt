add_library(Digraph "")
include_directories("../../include/digraph"
                    "../../include/bag"
                    "../../include/logger")
target_sources(Digraph PRIVATE
               Digraph.cpp
               "../../include/digraph/Digraph.h"
               "../../include/bag/Bag.h")
add_executable(DigraphTest
               DigraphTest.cpp
               Digraph.cpp
               "../../include/digraph/Digraph.h"
               "../../include/bag/Bag.h")
target_link_libraries(DigraphTest
                      Digraph
                      Logger)