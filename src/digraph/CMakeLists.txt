add_library(Digraph "")
include_directories("../../include/digraph"
                    "../../include/bag"
                    "../../include/logger")
target_sources(Digraph PRIVATE
               Digraph.cpp
               "../../include/digraph/Digraph.h"
               "../../include/bag/Bag.h"
               "../logger/Logger.cpp"
               "../../include/logger/Logger.h")
add_executable(DigraphTest
               DigraphTest.cpp)
target_link_libraries(DigraphTest
                      Digraph)