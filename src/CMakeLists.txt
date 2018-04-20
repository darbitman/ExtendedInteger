file(GLOB all_extendedmath_headers "../include/*.h")
set(SOURCES ExtendedMathTest.cpp ${all_extendedmath_headers})
add_executable(ExtendedMathTest ${SOURCES})
include_directories("../include"
                    "../include/nfa"
                    "../include/exception")
add_subdirectory(digraph)
add_subdirectory(NFA)
add_subdirectory(stack)
add_subdirectory(directedDFS)
add_subdirectory(bag)
add_subdirectory(exception)
add_subdirectory(logger)
target_link_libraries(ExtendedMathTest
                      NFA
                      Exception)