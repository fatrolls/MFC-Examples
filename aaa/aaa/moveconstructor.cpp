#include "functions.hpp"

template <class T>
class MoveResource
{
private:
   struct proxy
   {
      T * resource_;
   };
   T * resource_;
public:
   MoveResource (T * r) : resource_(r) { }  
   MoveResource (MoveResource &m) throw () // Move constructor (note non-const parameter)
      : resource_ (m.resource_)
   {
      m.resource_ = 0;
   }
   MoveResource (proxy p) throw () // The proxy move constructor
      : resource_(p.resource_)
   {
   }
   MoveResource & operator = (MoveResource &m) throw ()
   {
      // copy and swap idiom
      MoveResource temp (m);
      temp.swap (*this);
      return *this;
   }
   MoveResource & operator = (proxy p) throw ()
   {
      // copy and swap idiom
      MoveResource temp (p);
      temp.swap (*this);
      return *this;
   }
   void swap (MoveResource &m) throw ()
   {
      std::swap (this->resource_, m.resource_);
   }
   operator proxy () throw () // A helper conversion function. Note that it is non-const
   {
      proxy p;
      p.resource_ = this->resource_;
      this->resource_ = 0;
      return p;
   }
};

//The move constructor/assignment idiom plays an important role in the code snippet below.

MoveResource<int> func()
{
   MoveResource<int> m(new int());
   return m;
}
void MoveConstructor()
{
   MoveResource<int> a(func()); // Assuming this call is not return value optimized (RVO'ed).
}

