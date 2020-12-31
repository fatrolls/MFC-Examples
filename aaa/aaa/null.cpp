
#include "null.hpp"
#include <iostream>
void f(int x)//  和以前一样
{
    std::cout<<x;
}                   
void f(std::string *p) //  同上
{
    std::cout<<*p;
}              

void testNull()
{
    f(NullClass);                          //  将 NULL 转换为string*, 然后调用 f(string*)
}


void func (double *) {}
void func (int) {}

void nullptrtest(void)
{
   char * ch = nullptr_;        // ok
   func (nullptr_);             // Calls func(double *)
   func (0);                   // Calls func(int)
   void (Cnull::*pmf2)() = 0;      // ok
   void (Cnull::*pmf)() = nullptr_; // ok
   nullptr_t_ n1, n2;
   n1 = n2;
   //nullptr_t_ *null = &n1;    // Address can't be taken.
   if (nullptr_ == ch) {}       // ok
   if (nullptr_ == pmf) {}      // Valid statement; but fails on g++ 4.1.1-4.5 due to bug #33990
   // for GCC 4: if ((typeof(pmf))nullptr_ == pmf) {}
   const int n = 0;
   if (nullptr_ == n) {}        // Should not compile; but only Comeau shows an error.
   //int p = 0;
   //if (nullptr_ == p) {}      // not ok
   //g (nullptr_);              // Can't deduce T
   int expr = 0;
   char* ch3 = expr ? nullptr_ : nullptr_; // ch1 is the null pointer value
   //char* ch4 = expr ? 0 : nullptr_;     // error, types are not compatible
   //int n3 = expr ? nullptr_ : nullptr_;  // error, nullptr_ can’t be converted to int
   //int n4 = expr ? 0 : nullptr_;        // error, types are not compatible

   h( 0 );                // deduces T = int
   h( nullptr_ );          // deduces T = nullptr_t_
   h( (float*) nullptr_ ); // deduces T = float*

   sizeof( nullptr_ );     // ok
   typeid( nullptr_ );     // ok
   throw nullptr_;         // ok
}