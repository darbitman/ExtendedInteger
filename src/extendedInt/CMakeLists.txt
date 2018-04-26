include_directories("../../include/extendedInt"
                    "../../include/NFA"
                    "../../include/exception")
add_library(ExtendedInt STATIC "")
set(ExtendedInt_Sources
    ExtendedInt.cpp
    "../../include/extendedInt/ExtendedInt.h")
target_sources(ExtendedInt
               PRIVATE
               ${ExtendedInt_Sources})
target_link_libraries(ExtendedInt
                      NFA
                      Exception)

add_library(UnsignedExtendedInt STATIC "")
set(UnsignedExtendedInt_Sources
    UnsignedExtendedInt.cpp
    "../../include/extendedInt/UnsignedExtendedInt.h")
target_sources(UnsignedExtendedInt
               PRIVATE
               ${UnsignedExtendedInt_Sources})
target_link_libraries(UnsignedExtendedInt
                      ExtendedInt)
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
               ${SignedExtendedInt_Sources})
target_link_libraries(SignedExtendedInt
                      ExtendedInt)
add_executable(SignedExtendedIntTest
               SignedExtendedIntTest.cpp)
target_link_libraries(SignedExtendedIntTest
                      SignedExtendedInt)