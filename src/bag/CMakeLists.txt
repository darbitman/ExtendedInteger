include_directories("../../include/bag"
                    "../../include/logger")
add_executable(BagTest
               BagTest.cpp
               "../../include/bag/Bag.h")
target_link_libraries(BagTest
                      Logger)