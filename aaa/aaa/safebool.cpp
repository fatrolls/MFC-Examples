#include "safebool.hpp"
int safa (void)
{
   Testable t1;
   AnotherTestable t2;
   if (t1) {} // Works as expected
#if 0
   if (t2 == t1) {} // Fails to compile
   if (t1 < 0) {} // Fails to compile
#endif
   return 0;
}

#include <iostream>

class Testable_with_virtual : public safe_bool<> {
public:
   virtual ~Testable_with_virtual () {}
protected:
   virtual bool boolean_test() const {
      // Perform Boolean logic here
      return true;
   }
};

class Testable_without_virtual : 
   public safe_bool <Testable_without_virtual> // CRTP idiom
{
public:
   /* NOT virtual */ bool boolean_test() const {
      // Perform Boolean logic here
      return false;
   }
};



int safb (void)
{
   Testable_with_virtual t1, t2;
   Testable_without_virtual p1, p2;
   if (t1) {}
   if (p1 == false) 
   {
      std::cout << "p1 == false\n";
   }
#if 0
   if (p1 == p2) {} // Does not compile, as expected
   if (t1 != t2) {} // Does not compile, as expected
#endif
   return 0;
}
