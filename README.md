# ExtendedInteger  
This library allows users to utilize signed and unsigned integers that are larger than native 64-bit integers. This library dynamically adjusts the internal memory structure to store whatever size that is required to store your ExtendedIntegers.  
## Usage  
### Installation
1. Download repository  
2. Build project files/makefiles using cmake  
3. Install library  
4. include header  
### Here are some examples of how to declare/define extended integers  
> uextint foo("1234567890")  
> uextint foo2(123456)  
> uextint foo3(0x123ABC)  
> extint bar("-1234567890")  
> extint bar2(-123456)  
> extint bar3(123456)  
> extint bar4(0x123ABC)  
#### In order to achieve the arbitrarily large size, you MUST use the string input
