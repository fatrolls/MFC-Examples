#include <iostream>
#include <stdexcept>
#include <cassert>

struct BType {
   BType (char const *) { throw std::runtime_error("B Error"); }
};
struct CType {
   CType (char const *) { throw std::runtime_error("C Error"); }
};
class AType {
   BType b_;
   CType c_;
   enum TrackerType { NONE, ONE, TWO };
public:
   AType( TrackerType tracker = NONE)
      try    // A constructor try block.
      : b_((tracker = ONE, "hello")) // Can throw std::exception
      , c_((tracker = TWO, "world")) // Can throw std::exception
   {
      assert(tracker == TWO);
      // ... constructor body ...
   }
   catch (std::exception const & e)
   {
      if (tracker == ONE) {
         std::cout << "B threw: " << e.what() << std::endl;
      }
      else if (tracker == TWO) {
         std::cout << "C threw: " << e.what() << std::endl;
      }
      throw;
   }
};

int constructorTry (void) 
{
   try {
      AType a;
   }
   catch (std::exception const & e) {
      std::cout << "Caught: " << e.what() << std::endl;
   }
   return 0;       
}