# ExtendedInteger  
This library allows users to utilize signed and unsigned integers that are larger than native 64-bit integers. This library dynamically adjusts the internal memory structure to store whatever size that is required to store your ExtendedIntegers.  
## Usage  
### Installation
1. Download repository  
2. Build project files/makefiles using cmake  
3. Install library  
4. Add the following to your cmake project  
   find_package(ExtendedInteger REQUIRED)  
   target_include_directories(<your_target> PRIVATE ${EXTENDEDINTEGER_INCLUDE_DIRS})  
   target_link_libraries(<your_target> PRIVATE ${EXTENDEDINTEGER_LIBRARIES})  
5. Include header in your project  
   #include "ExtendedInteger.h"  
### Here are some examples of how to declare/define extended integers  
> uextint foo("1234567890")  
> uextint foo2(123456)  
> uextint foo3(0x123ABC)  
> extint bar("-1234567890")  
> extint bar2(-123456)  
> extint bar3(123456)  
> extint bar4(0x123ABC)  
#### In order to achieve the arbitrarily large size, you MUST use the string input
### Supported operations
> operator= (assignment)  
> operator+ (addition)  
> operator* (multiplication)  
> operator/ (division)  
> operator% (mod)
> operator== (relational equality)  
> operator!= (relational inequality)  
> operator\> (greater than)  
> operator\>= (greater than or equal)  
> operator< (less than)  
> operator<= (less than or equal)  
> operator>> (shift)  
> operator<< (shift)  
> operator& (bitwise and)  
> operator| (bitwise or)  
> operator^ (bitwise xor)  
> operator++ (pre-/post-fix increment)  
> operator-- (pre-/post-fix decrement)  
> operator~ (bitwise not)  
> operator<< (ostream)  
