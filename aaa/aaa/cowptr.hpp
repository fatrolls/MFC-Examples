#ifndef COWPTR_HPP
#define COWPTR_HPP
#include "boost/tr1/memory.hpp"
#include <memory>

template <class T>
class CowPtr
{
public:
   typedef std::tr1::shared_ptr<T> RefPtr;

private:
   RefPtr m_sp;

   void detach()
   {
      T* tmp = m_sp.get();
      if( !( tmp == 0 || m_sp.unique() ) ) {
         m_sp = RefPtr( new T( *tmp ) );
      }
   }

public:
   CowPtr(T* t)
      :   m_sp(t)
   {}
   CowPtr(const RefPtr& refptr)
      :   m_sp(refptr)
   {}
   CowPtr(const CowPtr& cowptr)
      :   m_sp(cowptr.m_sp)
   {}
   CowPtr& operator=(const CowPtr& rhs)
   {
      m_sp = rhs.m_sp; // no need to check for self-assignment with boost::shared_ptr
      return *this;
   }
   const T& operator*() const
   {
      return *m_sp;
   }
   T& operator*()
   {
      detach();
      return *m_sp;
   }
   const T* operator->() const
   {
      return m_sp.operator->();
   }
   T* operator->()
   {
      detach();
      return m_sp.operator->();
   }
};
/*
CowPtr<String> s1 = "Hello";
char &c = s1->operator[](4); // Non-const detachment does nothing here
CowPtr<String> s2(s1); // Lazy-copy, shared state
c = '!'; // Uh-oh
*/
#endif //COWPTR_HPP