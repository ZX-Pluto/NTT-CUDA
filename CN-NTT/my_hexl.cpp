#include "my_hexl.h"

using namespace std;
#define cp complex<double>

  
template <typename T>
void print_vector(vector<T> vector_temp){
    cout << "{";
    for(auto item : vector_temp) cout << item << ",";
    cout << "\b}";
}

template <typename T>
void print_array(T *array_temp,size_t len){
    cout << "{";
    for (size_t i = 0; i < len; i++)  cout << array_temp[i] << ",";
    cout << "\b}";
}

// #define HEXL_CHECK(cond, expr)                              \
//   if (!(cond)) {                                            \
//     LOG(ERROR) << expr << " in function: " << __FUNCTION__  \
//                << " in file: " __FILE__ << ":" << __LINE__; \
//     throw std::runtime_error("Error. Check log output");    \
//   }

// #define HEXL_VLOG(N, rest) \
//   do {                     \
//     if (VLOG_IS_ON(N)) {   \
//       VLOG(N) << rest;     \
//     }                      \
//   } while (0);


// Returns base^exp mod modulus
uint64_t PowMod(uint64_t base, uint64_t exp, uint64_t modulus) {
  base %= modulus;
  uint64_t result = 1;
  while (exp > 0) {
    if (exp & 1) {
      result = MultiplyMod(result, base, modulus);
    }
    base = MultiplyMod(base, base, modulus);
    exp >>= 1;
  }
  return result;
}

// Returns true whether root is a degree-th root of unity
// degree must be a power of two.
bool IsPrimitiveRoot(uint64_t root, uint64_t degree, uint64_t modulus) {
  if (root == 0) {
    return false;
  }
//   HEXL_CHECK(IsPowerOfTwo(degree), degree << " not a power of 2");

//   HEXL_VLOG(4, "IsPrimitiveRoot root " << root << ", degree " << degree
//                                        << ", modulus " << modulus);
  if(!IsPowerOfTwo(degree)){ std::cout << degree << " not a power of 2" << std::endl; exit(0);}
  // Check if root^(degree/2) == -1 mod modulus
  return PowMod(root, degree / 2, modulus) == (modulus - 1);
}

/// @brief Returns whether or not num is a power of two
bool IsPowerOfTwo(uint64_t num) { return num && !(num & (num - 1)); }

// /// @brief Returns floor(log2(x))
// inline uint64_t Log2(uint64_t x) { return MSB(x); }

// inline bool IsPowerOfFour(uint64_t num) {
//   return IsPowerOfTwo(num) && (Log2(num) % 2 == 0);
// }

// /// @brief Returns the maximum value that can be represented using \p bits bits
// inline uint64_t MaximumValue(uint64_t bits) {
//   HEXL_CHECK(bits <= 64, "MaximumValue requires bits <= 64; got " << bits);
//   if (bits == 64) {
//     return (std::numeric_limits<uint64_t>::max)();
//   }
//   return (1ULL << bits) - 1;
// }

// uint64_t BarrettReduce128_mod(uint64_t x, uint64_t modulus)
// {
  
// }

void MultiplyUInt64(uint64_t x, uint64_t y, uint64_t* prod_hi,
                           uint64_t* prod_lo) {
  uint128_t prod = MultiplyUInt64(x, y);
  *prod_hi = static_cast<uint64_t>(prod >> 64);
  *prod_lo = static_cast<uint64_t>(prod);
}

uint128_t MultiplyUInt64(uint64_t x, uint64_t y) {
  return uint128_t(x) * uint128_t(y);
}

uint64_t MultiplyMod(uint64_t x, uint64_t y, uint64_t modulus) {
//   HEXL_CHECK(modulus != 0, "modulus == 0");
//   HEXL_CHECK(x < modulus, "x " << x << " >= modulus " << modulus);
//   HEXL_CHECK(y < modulus, "y " << y << " >= modulus " << modulus);
  if(modulus == 0) { std::cout << "modulus == 0" << std::endl; exit(0);}
  if(!(x < modulus)) { std::cout << "x " << x << " >= modulus " << modulus << std::endl; exit(0);}
  if(!(y < modulus)) { std::cout << "y " << y << " >= modulus " << modulus << std::endl; exit(0);}
  uint64_t prod_hi, prod_lo;
  MultiplyUInt64(x, y, &prod_hi, &prod_lo);

  return BarrettReduce128(prod_hi, prod_lo, modulus);
}

uint64_t BarrettReduce128(uint64_t input_hi, uint64_t input_lo,
                                 uint64_t modulus) {
//   HEXL_CHECK(modulus != 0, "modulus == 0")
  if(modulus == 0) { std::cout << "modulus == 0" << std::endl; exit(0);}
  uint128_t n = (static_cast<uint128_t>(input_hi) << 64) |
                (static_cast<uint128_t>(input_lo));

  return n % modulus;
  // TODO(fboemer): actually use barrett reduction if performance-critical
}

uint64_t GenerateInsecureUniformRandomValue(uint64_t min_value,
                                                   uint64_t max_value) {
//   HEXL_CHECK(min_value < max_value, "min_value must be > max_value");

  static std::random_device rd;
  static std::mt19937 mersenne_engine(rd());
  std::uniform_int_distribution<uint64_t> distrib(min_value, max_value - 1);

  return distrib(mersenne_engine);
}

uint64_t Log2(uint64_t x) { return MSB(x); }

uint64_t MSB(uint64_t input) {
  return static_cast<uint64_t>(std::log2l(input));
}

uint64_t InverseMod(uint64_t input, uint64_t modulus) {
  uint64_t a = input % modulus;
  // HEXL_CHECK(a != 0, input << " does not have a InverseMod");
  if(a == 0) {std::cout << input << " does not have a InverseMod" << std::endl; exit(0);}

  if (modulus == 1) {
    return 0;
  }

  int64_t m0 = static_cast<int64_t>(modulus);
  int64_t y = 0;
  int64_t x = 1;
  while (a > 1) {
    // q is quotient
    int64_t q = static_cast<int64_t>(a / modulus);

    int64_t t = static_cast<int64_t>(modulus);
    modulus = a % modulus;
    a = static_cast<uint64_t>(t);

    // Update y and x
    t = y;
    y = x - q * y;
    x = t;
  }

  // Make x positive
  if (x < 0) x += m0;

  return uint64_t(x);
}

uint64_t GeneratePrimitiveRoot(uint64_t degree, uint64_t modulus) {
  // We need to divide modulus-1 by degree to get the size of the quotient group
  uint64_t size_entire_group = modulus - 1;

  // Compute size of quotient group
  uint64_t size_quotient_group = size_entire_group / degree;

  for (int trial = 0; trial < 200; ++trial) {
    uint64_t root = GenerateInsecureUniformRandomValue(0, modulus);
    root = PowMod(root, size_quotient_group, modulus);

    if (IsPrimitiveRoot(root, degree, modulus)) {
      return root;
    }
  }
//   HEXL_CHECK(false, "no primitive root found for degree "
//                         << degree << " modulus " << modulus);
  return 0;
}

// int main()
// {
//     uint64_t g = GeneratePrimitiveRoot(1024<<1,12289);
//     std::cout << "g = " << g << std::endl;
//     std::cout << Log2(1024) << std::endl;
// }