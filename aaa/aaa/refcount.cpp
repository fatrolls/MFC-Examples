#include "refcount.hpp"
RCObject::RCObject()
        : refCount(0), shareable(true) {}
RCObject::RCObject(const RCObject&)
        : refCount(0), shareable(true) {}
RCObject& RCObject::operator=(const RCObject&)
{
    return *this;
}
RCObject::~RCObject() {}               
// virtual dtors must always be implemented, even if
// they are pure virtual and do nothing (see also Item M33 and Item E14)
void RCObject::addReference()
{
    ++refCount;
}
void RCObject::removeReference()
{
    if (--refCount == 0) delete this;
}
void RCObject::markUnshareable()
{
    shareable = false;
}
bool RCObject::isShareable() const
{
    return shareable;
}
bool RCObject::isShared() const
{
    return refCount > 1;
}



template<class T>
RCPtr<T>::RCPtr(T* realPtr): pointee(realPtr)
{
    init();
}
template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs): pointee(rhs.pointee)
{
    init();
}
template<class T>
void RCPtr<T>::init()
{
    if (pointee == 0) {                // if the dumb pointer is
        return;                          // null, so is the smart one
    }
    if (pointee->isShareable() == false) {           // if the value
        pointee = new T(*pointee);                   // isn't shareable,
    }                                              // copy it
    pointee->addReference();             // note that there is now a
}                                    // new reference to the value
template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
    if (pointee != rhs.pointee) {          // skip assignments
        // where the value
        // doesn't change
        if (pointee) {
            pointee->removeReference();        // remove reference to
        }                                    // current value
        pointee = rhs.pointee;               // point to new value
        init();                              // if possible, share it
    }                                      // else make own copy
    return *this;
}
template<class T>
RCPtr<T>::~RCPtr()
{
    if (pointee)pointee->removeReference();
}
template<class T>
T* RCPtr<T>::operator->() const
{
    return pointee;
}
template<class T>
T& RCPtr<T>::operator*() const
{
    return *pointee;
}


RString::StringValue::StringValue(const char *initValue)
{
    data = new char[strlen(initValue) + 1];
    strcpy(data, initValue);
}
RString::StringValue::StringValue(const StringValue& rhs)
{
    data = new char[strlen(rhs.data) + 1];
    strcpy(data, rhs.data);
}
RString::StringValue::~StringValue()
{
    delete [] data;
}
