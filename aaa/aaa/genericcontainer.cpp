#include <algorithm>
// construct helper using placement new:
template <class T1, class T2>
void construct (T1 &p, const T2 &value)
{
   new (&p) T1(value); // T must support copy-constructor
}

// destroy helper to invoke destructor explicitly.
template <class T>
void destroy (T const &t)  throw ()
{
   t.~T(); // T must support non-throwing destructor
}

template<class T>
class Stack
{
   int size_;
   T * array_;
   int top_;
public:
   Stack (int size=10)
      : size_(size),
      array_ (static_cast <T *>(::operator new (sizeof (T) * size))), // T need not support default construction
      top_(0)
   { }
   void push (const T & value)
   {
      construct (array_[top_++], value); // T need not support assignment operator.
   }
   T top ()
   {
      return array_[top_ - 1]; // T should support copy construction
   }
   void pop()
   {
      destroy (array_[--top_]);     // T destroyed
   }
   ~Stack () throw()
   {
      std::for_each(array_, array_ + top_, destroy<T>);
      ::operator delete(array_); // Global scope operator delete.
   }
};
class X
{
public:
   X (int) {} // No default constructor for X.
private:
   X & operator = (const X &); // assignment operator is private
};
int genericcontainer (void)
{
   Stack <X> s; // X works with Stack!

   return 0;
}