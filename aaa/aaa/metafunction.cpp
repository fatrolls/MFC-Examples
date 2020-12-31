#include "functions.hpp"

template <bool, class L, class R>
struct IF
{
   typedef R type; 
};

template <class L, class R>
struct IF<true, L, R>
{
   typedef L type; 
};
//Type Selection
IF<false, int, long>::type i; // is equivalent to long i;
IF<true,  int, long>::type j; // is equivalent to int j;

template <int N>
struct Factorial 
{
   enum { value = N * Factorial<N - 1>::value };
};

template <>
struct Factorial<0> 
{
   enum { value = 1 };
};

// Factorial<4>::value == 24
// Factorial<0>::value == 1
void foometa()
{
   int x = Factorial<4>::value; // == 24
   int y = Factorial<0>::value; // == 1
}

template <class T, unsigned int CAPACITY>
class Queue 
{
   T array[CAPACITY];
   typename IF<(CAPACITY <= 256),
      unsigned char,
      typename IF<(CAPACITY <= 65536), unsigned short, unsigned int>::type
   >::type size;
   // ...
};