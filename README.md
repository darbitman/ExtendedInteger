# extendedmath

This library provides users to utilize signed and unsigned integers that are larger than native 64-bit integers. The library allows for arbitrarily large integers in multiples of 32-bits.

### The following types are natively supported  
> **uextint128_t** (128-bit unsigned extended int)  
> **uextint256_t** (256-bit unsigned extended int)  
> **uextint512_t** (512-bit unsigned extended int)  
> **extint128_t** (128-bit signed extended int)  
> **extint256_t** (256-bit signed extended int)  
> **extint512_t** (512-bit signed extended int)  
##### If you need extended integers with more bits, see _typedefs.h_ for examples how to define them  

### Here are some examples of how to declare/define extended integers  
> uextint128_t foo("123456789")  
> uextint128_t foo(1234)  
> extint128_t foo(-1234)  
> extint128_t foo(1234)  

### The following operations are supported  
> multiply  
> divide  
> mod  
> add  
> subtract  
> ==  
> \>  
> \>=  
> <  
> <=  
> right shift  
> left shift  
> bitwise and  
> bitwise or  
> bitwise xor  
> bitwise not  
> prefix/postfix increment/decrement  

### The following math operations are currently supported as well
> logBase10  
> log  
> power  
> factorial  
