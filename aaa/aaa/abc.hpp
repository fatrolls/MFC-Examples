#pragma  once
#include <iostream> 
#include <functional>
using namespace std; 
struct A 
{ 
   virtual void f() {cout<<"A::f"<<endl;} 
}; 
struct B : A 
{ 
   virtual void f() {cout<<"B::f"<<endl;} 
}; 
struct C : B 
{ 
   using A::f; 
}; 
void testABC() ;


class Int {
public:
   Int(int x) : val(x) {}
   int get() { return val; }
private:
   int val;
};
void ucopy();
int valref( );

class Base1{

public:
   Base1();
   virtual ~Base1();
   virtual void speak();
   virtual Base1* clone() const;
protected:
   float data_base1;
};
class Base2{

public:
   Base2();
   virtual ~Base2();
   virtual void mumble();
   virtual Base2* clone() const;
protected:
   float data_base2;
};

class Derived:public Base1,public Base2{

public:
   Derived();
   virtual ~Derived();
   virtual Derived* clone() const;
protected:
   float data_derived;
};

/////////////////////Calling Virtuals During Initialization
class Base3 
{
};
template <class D>
class InitTimeCaller : public Base3 
{
protected:
   InitTimeCaller () {
      D::foo ();
      D::bar ();
   }
};
class Derived3 : public InitTimeCaller <Derived3> 
{
public:
   Derived3 () : InitTimeCaller <Derived3> () {
      cout << "Derived3::Derived()\n";
   }
   static void foo () {
      cout << "Derived3::foo()\n";
   }
   static void bar () {
      cout << "Derived3::bar()\n";
   }
};

/////////////////////
template<class T> 
inline void checked_delete(T * x)
{
   typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
   (void) sizeof(type_must_be_complete);
   delete x;
}
template<class T> 
struct checked_deleter : std::unary_function <T *, void>
{
   void operator()(T * x) const
   {
      checked_delete(x);//boost::
   }
};

///////////////////////////////Coercion by Member Template
template <class T>
class Ptr
{
public:
   Ptr () {}

   Ptr (Ptr const & p)
      : ptr (p.ptr)
   {
      std::cout << "Copy constructor\n";
   }

   // Supporting coercion using member template constructor.
   // This is not a copy constructor, but behaves similarly.
   template <class U>
   Ptr (Ptr <U> const & p)
      : ptr (p.ptr) // Implicit conversion from U to T required
   {
      std::cout << "Coercing member template constructor\n";
   }

   // Copy assignment operator.
   Ptr & operator = (Ptr const & p)
   {
      ptr = p.ptr;
      std::cout << "Copy assignment operator\n";
      return *this;
   }

   // Supporting coercion using member template assignment operator.
   // This is not the copy assignment operator, but works similarly.
   template <class U>
   Ptr & operator = (Ptr <U> const & p)
   {
      ptr = p.ptr; // Implicit conversion from U to T required
      std::cout << "Coercing member template assignment operator\n";
      return *this;
   } 

   T *ptr;
};

template <class T>
class Array
{
public:
   Array () {}
   Array (Array const & a)
   {
      std::copy (a.array_, a.array_ + SIZE, array_);
   }

   template <class U>
   Array (Array <U *> const & a)
   {
      std::copy (a.array_, a.array_ + SIZE, array_);
   }

   template <class U>
   Array & operator = (Array <U *> const & a)
   {
      std::copy (a.array_, a.array_ + SIZE, array_);
   }

   enum { SIZE = 10 };
   T array_[SIZE];
};

////////////////////////////////

class Game
{
public:
   static Game createSinglePlayerGame() { return Game(0); } // named constructor
   static Game createMultiPlayerGame() { return Game(1); }  // named constructor
protected:
   Game (int game_type);
};

/////////////////////////////////Named Parameter
class X
{
public:
   int a;
   char b;

   X() : a(-999), b('C') {}  // Initialize with default values, if any.
   X & setA(int i) { a = i; return *this; } // non-const function
   X & setB(char c) { b = c; return *this; } // non-const function

   static X create() {
      return X();
   }
};

////////////////////////////////////Thin Template

// Not a template
class VectorBase {
   void insert (void *); 
   void *at (int index);
};

template <class T>
class Vector  // Thin template 
   : VectorBase 
{
   inline void insert (T *t) {
      VectorBase::insert (t);
   }
   inline T *at (int index) {
      return VectorBase::at (index);
   }
};

#include <map> 
#include <string> 
#include <memory> 
template <class Value>
struct Directory
{
   typedef std::map <std::string, Value, std::less<string>, std::allocator<std::string> > type;
#if 0
   typedef _Select1st<typename type::value_type> KeySelector;
   typedef _Select2nd<typename type::value_type> ValueSelector;
#endif
};

///////////////////////////////Virtual Friend Function
class BaseF {
public:
   friend ostream& operator << (ostream& o, const BaseF& b);
   // ...
protected:
   virtual void print(ostream& o) const
   { ; }
};

inline std::ostream& operator<< (std::ostream& o, const BaseF& b)
{
   b.print(o); // delegate the work to a polymorphic member function.
   return o;
}

class DerivedF : public BaseF {
protected:
   virtual void print(ostream& o) const
   { ; }
};