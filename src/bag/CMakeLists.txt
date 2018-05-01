add_library(Bag "")
include_directories("../../include/bag"
                    "../../include/logger")
target_sources(Bag
               PRIVATE
               "../../include/bag/Bag.h"
               "../../include/logger/Logger.h"
               "../logger/Logger.cpp")
add_executable(BagTest
               BagTest.cpp
               "../../include/bag/Bag.h")
target_link_libraries(BagTest
                      Logger)