file(GLOB all_extendedmath_headers "../include/*.h")
set(SOURCES ExtendedMath.cpp ${all_extendedmath_headers})
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories("../include"
                    "../include/nfa"
                    "../include/exception")
add_subdirectory(digraph)
add_subdirectory(NFA)
add_subdirectory(Stack)
add_subdirectory(directedDFS)
add_subdirectory(bag)
add_subdirectory(exception)
target_link_libraries(${PROJECT_NAME} NFA)