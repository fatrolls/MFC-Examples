// envelope_letter.cpp
// complete example for
// http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Envelope_Letter
// .
// Rough draft.
// FIXME: horrific memory leakage.
// FIXME: way too much coupling between classes.
// FIXME: Surely there's a way to do this without a bunch of "dynamic_cast"?
// FIXME: multiplying a complex times 0 or 0.0 returns a complex.
//     Should it metamorphose to a integer or a real instead?
// 2010-06-26:DAV: cleanup.
// 2010-06-25:DAV: technically "runs", and gives numerically correct results.
// 2010-06-21:DAV: David Cary http://en.wikibooks.org/wiki/User:DavidCary started
// public domain.
#pragma  once
#include <iostream>

// "Number" is the Envelope class
// Client code only uses the "Number" class.
// Client code never directly uses "RealNumber, "ComplexNumber", etc.
class Number {
public:
   Number();
   Number( int i );
   Number( double f );
   Number( double x, double y );
   virtual Number * clone();
   Number( const Number &copy ): letter(copy.letter->clone()) {
   }; // nice class
   virtual Number & operator= (const Number &rhs); // nice class
   virtual ~Number(){ // destructor
      delete letter;
      letter = 0;
   };
   virtual Number * multiply ( const Number & rhs ){
      letter = letter->multiply( rhs );
      return this;
   };
   // use Virtual Friend Function idiom,
   // since friend functions can't be made virtual.
   virtual void print(std::ostream& out) const{
      letter->print(out);
   };
   friend std::ostream& operator<<( std::ostream& out, const Number& number){
      number.print(out);
      return out;
   };
   // FIXME: should this be private or protected?
   // "letter" always points to an object of one of the child classes,
   // never to an object of the Number base class.
   Number * letter;
};

// file Number.hpp ends here
void test_Number();