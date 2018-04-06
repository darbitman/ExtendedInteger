add_library(Digraph "")
include_directories("../../include/digraph")
target_sources(Digraph PRIVATE
               Digraph.cpp
               "../../include/digraph/Digraph.h")
add_executable(DigraphTest
               DigraphTest.cpp
               Digraph.cpp
               "../../include/digraph/Digraph.h")
target_link_libraries(DigraphTest Digraph)