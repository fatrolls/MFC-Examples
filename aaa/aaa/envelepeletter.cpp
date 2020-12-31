
// file Number.cpp

#include "number.hpp"
#include <cassert>
Number * Number::clone(){
   Number * r = new Number();
   if( letter ){
      r->letter = letter->clone();
   }else{
      r->letter = 0;
   };
   return r;
};
Number & Number::operator= (const Number &rhs){
   if( this != &rhs ){
      delete letter;
      letter = 0;
      letter = rhs.letter->clone();
   };
   return *this;
}; // nice class

// RealNumber and ComplexNumber are two kinds of Letter classes
// They derive from the Envelope class Number
// in its role as the class defining the interface to the implementations.
// (Although they technically inherit a Number * letter member,
// ComplexNumber never uses it -- its letter member is always the NULL pointer).

class IntegerNumber;
class RealNumber;
class ComplexNumber;

class ComplexNumber : public Number {
public:
   ComplexNumber( double x, double y );
   Number * multiply( const ComplexNumber & rhs);
   Number * multiply( const Number & rhs);
   void print(std::ostream& out) const{
      out << "(" << first_part << ", " << second_part << ")";
   };
private:
   double first_part;
   double second_part;
};
class IntegerNumber : public Number {
public:
   IntegerNumber( int i ): the_integer(i) {
      std::cout << "IntegerNumber:: creating IntegerNumber." << std::endl;
   };
   IntegerNumber * clone(){
      IntegerNumber * r = new IntegerNumber(the_integer);
      return r;
   };
   void print(std::ostream& out) const{
      out << the_integer;
   };
   Number * multiply ( const Number & rhs ){
      std::cout << "IntegerNumber:: multiply by some Number." << std::endl;
      // if letter and rhs are both Integers, letter->add returns an Integer
      // if letter is a Complex, or rhs is a Complex, what comes back is Complex

      const Number * the_letter = 0;
      if( rhs.letter ){ // peel off redundant layer of abstraction
         std::cout << "rhs is an envelope -- extract the letter" << std::endl;
         the_letter = rhs.letter;
      }else{
         std::cout << "rhs is a letter." << std::endl;
         the_letter = &rhs;
      };

      const IntegerNumber * int_rhs = dynamic_cast<const IntegerNumber *>(the_letter);
      if( int_rhs ){
         std::cout << "IntegerNumber:: multiply by IntegerNumber." << std::endl;
         the_integer *= int_rhs->the_integer;
         return this;
      };
      // since the dynamic_cast "failed",
      // the_letter is clearly *not* an IntegerNumber.
      // Perhaps it's Real? or Complex?
      std::cout << "IntegerNumber:: metamorphizing to Complex in order to multiply..." << std::endl;
      ComplexNumber * r = new ComplexNumber( the_integer, 0.0 );
      r->multiply(rhs);
      std::cout << "IntegerNumber:: finished metamorphosis and multiply by some Number..." << std::endl;
      return r;
   };
   // FIXME: shouldn't this be private?
   // private:
   int the_integer;
};
class RealNumber : public Number {
public:
   RealNumber( double x ): real_part(x) {
      std::cout << "RealNumber:: creating RealNumber." << std::endl;
   };
   void print(std::ostream& out) const{
      out << real_part;
   };
   Number * multiply ( const Number & rhs ){
      std::cout << "RealNumber:: multiply by some Number." << std::endl;
      // Should we try to check if the rhs is an integer or real,
      // before deferring to CompledNumber::multiply?
      std::cout << "RealNumber:: metamorphizing to Complex in order to multiply..." << std::endl;
      ComplexNumber * r = new ComplexNumber( real_part, 0.0 );
      r->multiply(rhs);
      std::cout << "IntegerNumber:: finished metamorphosis and multiply by some Number..." << std::endl;
      return r;
   };
   // FIXME: shouldn't this be private?
   // private:
   double real_part;
};

ComplexNumber::    
   ComplexNumber( double x, double y ):
first_part(x), second_part(y) {
   std::cout << "ComplexNumber:: creating ComplexNumber." << std::endl;
};
Number * ComplexNumber::multiply( const ComplexNumber & rhs){
   std::cout << "ComplexNumber:: multiply by ComplexNumber." << std::endl;
   double a = first_part*rhs.first_part - second_part*rhs.second_part;
   double b = first_part*rhs.second_part + second_part*rhs.first_part;
   first_part = a;
   second_part = b;
   if( 0 == second_part ){
      std::cout << "ComplexNumber:: metamorphosis" << std::endl;
      return( new RealNumber(first_part) ); // metamorphize
   }
   return this;
}
Number * ComplexNumber::multiply( const Number & rhs){
   std::cout << "ComplexNumber:: multiply by some Number." << std::endl;

   const Number * the_letter = 0;
   if( rhs.letter ){ // peel off redundant layer of abstraction
      std::cout << "rhs is an envelope -- extract the letter" << std::endl;
      the_letter = rhs.letter;
   }else{
      std::cout << "rhs is a letter." << std::endl;
      the_letter = &rhs;
   };

   const ComplexNumber * complex_rhs = dynamic_cast<const ComplexNumber *>(the_letter);
   if( complex_rhs ){
      std::cout << "ComplexNumber:: multiply by ComplexNumber." << std::endl;
      std::cout << "ComplexNumber:: multiplying ..." << std::endl;
      return( multiply( *complex_rhs ) );
   };
   const IntegerNumber * integer_rhs = dynamic_cast<const IntegerNumber *>(the_letter);
   if( integer_rhs ){
      first_part *= integer_rhs->the_integer;
      second_part *= integer_rhs->the_integer;
      return this;
   };
   const RealNumber * real_rhs = dynamic_cast<const RealNumber *>(the_letter);
   if( real_rhs ){
      first_part *= real_rhs->real_part;
      second_part *= real_rhs->real_part;
      return this;
   };
   // unexpected: what else could it be?
   assert(0);
}

Number::Number(): letter(0) {
   std::cout << "Number:: creating default Number()." << std::endl;
};
Number::Number( int i ): letter(0) {
   std::cout << "Number:: creating IntegerNumber." << std::endl;
   letter = new IntegerNumber( i );
};
Number::Number( double f ): letter(0) {
   std::cout << "Number:: creating RealNumber." << std::endl;
   letter = new RealNumber( f );
};
Number::Number( double x, double y ): letter(0) {
   std::cout << "Number:: creating ComplexNumber." << std::endl;
   letter = new ComplexNumber( x, y );
};

/* Example client code: */

void print_it( Number &x ){
   std::cout << "value: " << x << std::endl;
};

void test_Number(){
   std::cout << "testing ..." << std::endl;
   Number a(2);
   Number b(3.1,7.5);
   Number c(3);

   std::cout << "testing a ..." << a << std::endl;
   std::cout << "testing b ..." << b << std::endl;

   std::cout << "testing function called with derived class ..." << std::endl;
   print_it(a);
   print_it(b);
   print_it(c);

   std::cout << "testing integer multiply : 3*2 ..." << std::endl;
   c.multiply(a);
   print_it(c);

   std::cout << "testing integer*complex multiply :" << a << "*" << b << " ..." << std::endl;
   a.multiply(b);
   print_it(a);
}
