class NonCopyable
{
protected:
   NonCopyable () {}
   ~NonCopyable () {} /// Protected non-virtual destructor
private: 
   NonCopyable (const NonCopyable &);
   NonCopyable & operator = (const NonCopyable &);
};
class CantCopy : private NonCopyable
{};

template <class T>
class NonCopyableT
{
protected:
   NonCopyableT () {}
   ~NonCopyableT () {} /// Protected non-virtual destructor
private: 
   NonCopyableT (const NonCopyableT &);
   T & operator = (const T &);
};
class CantCopyD : private NonCopyableT <CantCopyD>
{};

struct NoImplicitCopy
{
   NoImplicitCopy () {}
   explicit NoImplicitCopy (const NoImplicitCopy &) {}
};


//////////////////////////////////////////////Resource Acquisition Is Initialization
#include "nvi.hpp"
#if 0
class NonCopyable 
{
   NonCopyable (NonCopyable const &); // private copy constructor
   NonCopyable & operator = (NonCopyable const &); // private assignment operator
};
#endif
template <class T>
class AutoDelete : NonCopyable
{
public:
   AutoDelete (T * p = 0) : ptr_(p) {}
   ~AutoDelete () throw() { delete ptr_; } 
private:
   T *ptr_;
};

class ScopedLock : NonCopyable// Scoped Lock idiom
{
public:
   ScopedLock (ReaderWriterLock & l) : lock_(l) { lock_.acquire(); }
   ~ScopedLock () throw () { lock_.release(); } 
private:
   ReaderWriterLock& lock_;
};

///////////////////////////////////////Scope Guard
class ScopeGuard
{
public:
   ScopeGuard () 
      : engaged_ (true) 
   { /* Acquire resources here. */ }

   ~ScopeGuard ()  
   { 
      if (engaged_) 
      { /* Release resources here. */} 
   }
   void release () 
   { 
      engaged_ = false; 
      /* Resources no longer be released */ 
   }
private:
   bool engaged_;
};

