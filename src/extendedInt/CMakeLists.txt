add_library(ExtendedInt STATIC "")
include_directories("../../include/extendedInt"
                    "../../include/NFA"
                    "../../include/digraph"
                    "../../include/stack"
                    "../../include/bag"
                    "../../include/directedDFS"
                    "../../include/exception"
                    "../../include/logger")
set(ExtendedInt_Sources
    ExtendedInt.cpp
    "../../include/extendedInt/ExtendedInt.h")
set(StringValidation_Sources
    "../NFA/NFA.cpp"
    "../../include/NFA/NFA.h"
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
target_sources(ExtendedInt
               PRIVATE
               ${ExtendedInt_Sources}
               ${StringValidation_Sources})

add_library(UnsignedExtendedInt STATIC "")
set(UnsignedExtendedInt_Sources
    UnsignedExtendedInt.cpp
    "../../include/extendedInt/UnsignedExtendedInt.h")
target_sources(UnsignedExtendedInt
               PRIVATE
               ${ExtendedInt_Sources}
               ${UnsignedExtendedInt_Sources}
               ${StringValidation_Sources})
add_executable(UnsignedExtendedIntTest
               UnsignedExtendedIntTest.cpp)
target_link_libraries(UnsignedExtendedIntTest
                      UnsignedExtendedInt)

add_library(SignedExtendedInt STATIC "")
set(SignedExtendedInt_Sources
    SignedExtendedInt.cpp
    "../../include/extendedInt/SignedExtendedInt.h")
target_sources(SignedExtendedInt
               PRIVATE
               ${ExtendedInt_Sources}
               ${SignedExtendedInt_Sources}
               ${StringValidation_Sources})
add_executable(SignedExtendedIntTest
               SignedExtendedIntTest.cpp)
target_link_libraries(SignedExtendedIntTest
                      SignedExtendedInt)
                      
add_library(ExtendedInteger STATIC "")
target_sources(ExtendedInteger
               PRIVATE
               ${ExtendedInt_Sources}
               ${SignedExtendedInt_Sources}
               ${UnsignedExtendedInt_Sources}
               ${StringValidation_Sources})

configure_file(ExtendedInteger-config.cmake.in "${CMAKE_BINARY_DIR}/ExtendedInteger-config.cmake")
install(TARGETS ExtendedInteger DESTINATION lib)
