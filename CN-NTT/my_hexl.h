#include<bits/stdc++.h>
#include<complex>

// typedef long long uint64_t;
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;

uint64_t PowMod(uint64_t base, uint64_t exp, uint64_t modulus);
bool IsPrimitiveRoot(uint64_t root, uint64_t degree, uint64_t modulus);
bool IsPowerOfTwo(uint64_t num);
void MultiplyUInt64(uint64_t x, uint64_t y, uint64_t* prod_hi,
                           uint64_t* prod_lo);
uint128_t MultiplyUInt64(uint64_t x, uint64_t y);
uint64_t MultiplyMod(uint64_t x, uint64_t y, uint64_t modulus);
uint64_t BarrettReduce128(uint64_t input_hi, uint64_t input_lo,
                                 uint64_t modulus);
uint64_t GenerateInsecureUniformRandomValue(uint64_t min_value,
                                                   uint64_t max_value);
uint64_t GeneratePrimitiveRoot(uint64_t degree, uint64_t modulus);

uint64_t Log2(uint64_t x);

// Returns most-significant bit of the input
uint64_t MSB(uint64_t input);

uint64_t InverseMod(uint64_t input, uint64_t modulus);