#include "refcount3.hpp"
template<class T>
void RCIPtr<T>::init()
{
    if (counter->isShareable() == false) {
        T *oldValue = counter->pointee;
        counter = new CountHolder;
        counter->pointee = new T(*oldValue);
    }
    counter->addReference();
}
template<class T>
RCIPtr<T>::RCIPtr(T* realPtr)
        : counter(new CountHolder)
{
    counter->pointee = realPtr;
    init();
}
template<class T>
RCIPtr<T>::RCIPtr(const RCIPtr& rhs)
        : counter(rhs.counter)
{
    init();
}
template<class T>
RCIPtr<T>::~RCIPtr()
{
    counter->removeReference();
}
template<class T>
RCIPtr<T>& RCIPtr<T>::operator=(const RCIPtr& rhs)
{
    if (counter != rhs.counter) {
        counter->removeReference();
        counter = rhs.counter;
        init();
    }
    return *this;
}
template<class T>                          // implement the copy part of copy-on- write (COW)
void RCIPtr<T>::makeCopy()                 
{
    
    if (counter->isShared()) {
        T *oldValue = counter->pointee;
        counter->removeReference();
        counter = new CountHolder;
        counter->pointee = new T(*oldValue);
        counter->addReference();
    }
}
template<class T>                           // const access;no COW needed
const T* RCIPtr<T>::operator->() const       
{
    return counter->pointee;
}
template<class T>                           // non-const access; COW
T* RCIPtr<T>::operator->()                   
{
    makeCopy();    // needed
    return counter->pointee;
}
template<class T>                           // const access;no COW needed
const T& RCIPtr<T>::operator*() const        
{
    return *(counter->pointee);
}
template<class T>                           // non-const access; do the COW thing
T& RCIPtr<T>::operator*()                    
{
    makeCopy();     
    return *(counter->pointee);
}

