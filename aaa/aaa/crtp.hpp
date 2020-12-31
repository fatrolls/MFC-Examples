#pragma  once

#include "boost/tr1/type_traits.hpp"
template <class Derived>
class base_t
{
public:
   void intfc()
   {
      // ...
      static_cast<Derived*>(this)->implementation();
      // ...
   }

   static void static_intfc()
   {
      // ...
      Derived::static_implementation();
      // ...
   }

   // The default implementation may be (if exists) or should be (otherwise) 
   // overriden by inheriting in derived classes (see below)
   void implementation();
   static void static_implementation();
};

// The Curiously Recurring Template Pattern (CRTP)
class derived_1 : base_t<derived_1>
{
   public:
   // This class uses base variant of implementation
   //void implementation();

   // ... and overrides static_implementation
   static void static_implementation();
};

class derived_2 : base_t<derived_2>
{
public:
   // This class overrides implementation
   void implementation();

   // ... and uses base variant of static_implementation
   //static void static_implementation();
};
//////////////////////////////////////////////
// enable_if 
namespace{

	template <bool, class T = void> struct enable_if {};
	template <class T> struct enable_if<true, T> { typedef T type; };
	
	 
	   // following function is defined for all arithmetic types
	   template <class T>
	   typename enable_if<std::tr1::is_arithmetic<T>::value, T>::type 
	   foo(T t)
	{
	   return t;
	}
	
	// the enable_if template can be used either as the return type, or as an extra argument.
	template <class T>
	T foo2(T t, typename enable_if<std::tr1::is_arithmetic<T>::value, T>::type* dummy = 0);//??
}
//////////////////////////////////////////////////////
class ISerializable{
   virtual int serialize (char *& buffer, size_t & buf_size) const=0;
};
template <class T>
class Serializable : public T,   /// Parameterized Base Class Idiom
   public ISerializable
{
public:
   Serializable (const T &t = T()) : T(t) {}
   virtual int serialize (char *& buffer, size_t & buf_size) const
   {
      const size_t size = sizeof (T);
      if (size > buf_size)
         throw std::runtime_error("Insufficient memory!");

      memcpy (buffer, static_cast<const T *>(this), size);
      buffer += size;
      buf_size -= size;
      return size;
   }
};