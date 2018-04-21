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