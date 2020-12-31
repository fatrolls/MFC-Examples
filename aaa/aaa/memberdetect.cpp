#include <utility>
#include <iostream>
#include "functions.hpp"

template<typename T>
class DetectX
{
   struct Fallback { int X; }; // add member name "X"
   struct Derived : T, Fallback { };

   template<typename U, U> struct Check;

   typedef char ArrayOfOne[1];  // typedef for an array of size one.
   typedef char ArrayOfTwo[2];  // typedef for an array of size two.

   template<typename U> 
   static ArrayOfOne & func(Check<int Fallback::*, &U::X> *);

   template<typename U> 
   static ArrayOfTwo & func(...);//

public:
   typedef DetectX type;
   enum { value = sizeof(func<Derived>(0)) == 2 };
};

#define CREATE_MEMBER_DETECTOR(X)                                                   \
   template<typename T> class Detect_##X {                                             \
struct Fallback { int X; };                                                     \
struct Derived : T, Fallback { };                                               \
   \
   template<typename U, U> struct Check;                                           \
   \
   typedef char ArrayOfOne[1];                                                     \
   typedef char ArrayOfTwo[2];                                                     \
   \
   template<typename U> static ArrayOfOne & func(Check<int Fallback::*, &U::X> *); \
   template<typename U> static ArrayOfTwo & func(...);                             \
   public:                                                                           \
   typedef Detect_##X type;                                                        \
   enum { value = sizeof(func<Derived>(0)) == 2 };                                 \
};

CREATE_MEMBER_DETECTOR(first);
CREATE_MEMBER_DETECTOR(second);

template<typename T, typename RESULT, typename ARG1, typename ARG2>
class HasPolicy
{
   RESULT policy(ARG1, ARG2);//--
   template <typename U, RESULT (U::*)(ARG1, ARG2)> struct Check;
   template <typename U> static char func(Check<U, &U::policy> *);
   template <typename U> static int func(...);
public:
   typedef HasPolicy type;
   enum { value = sizeof(func<T>(0)) == sizeof(char) };
};

void memdetect(void)
{
   typedef std::pair<int, double> Pair;
   std::cout << ((Detect_first<Pair>::value && Detect_second<Pair>::value)? "Pair" : "Not Pair");
}