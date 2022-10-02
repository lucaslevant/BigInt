# BigInt
A complete calculator for integers from 2^-62 to 2^62 accomplished using extensive operator overloading
o	Allows for Addition, Subtraction, Multiplication, Division, Modulus, Exponentiation, Modular Exponentiation, as well as equality checks.
o	Supports numbers of any base between 2 and 36

Handling non-base 10 numbers:
capital letter A-Z in the string input are used to represent each digit of a number greater than 9. For example, the hexadecimal base (base 16), the letters A through F are included as digits. That is, 0 - 9 and then A - F (16 possibilities). However, the actual value of a digit (int form) is stored in the vector. For example, A will be stored as 10, B as 11, etc.

Application of the BigInt library:
BigInts are often used in cryptography applications. To demonstrate one of many applications of the BigInt library, included are a number of secret messageswe that have been encrypted. The BigInt library can be used to decipher these messages. 

IMPORTANT: position 0 in the vector is used to store the rightmost digit, and position 1 is used to store the second rightmost digit, and so on. This simplifys the arithmetic operations because it is cheaper to do push_back than insert for a vector.


**Exponenation by squaring is used because it has logarithmic runtime instead of a linear runtime**

Modular exponentiation explained:
https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
