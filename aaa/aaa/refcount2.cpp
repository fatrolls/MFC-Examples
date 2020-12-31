#include "refcount2.hpp"

RCObject2::RCObject2()
        : refCount(0), shareable(true) {}
RCObject2::RCObject2(const RCObject2&)
        : refCount(0), shareable(true) {}
RCObject2& RCObject2::operator=(const RCObject2&)
{
    return *this;
}
RCObject2::~RCObject2() {}
void RCObject2::addReference()
{
    ++refCount;
}
void RCObject2::removeReference()
{
    if (--refCount == 0) delete this;
}
void RCObject2::markUnshareable()
{
    shareable = false;
}
bool RCObject2::isShareable() const
{
    return shareable;
}
bool RCObject2::isShared() const
{
    return refCount > 1;
}



template<class T>
void RCPtr2<T>::init()
{
    if (pointee == 0) return;
    if (pointee->isShareable() == false) {
        pointee = new T(*pointee);
    }
    pointee->addReference();
}
template<class T>
RCPtr2<T>::RCPtr2(T* realPtr)
        : pointee(realPtr)
{
    init();
}
template<class T>
RCPtr2<T>::RCPtr2(const RCPtr2& rhs)
        : pointee(rhs.pointee)
{
    init();
}
template<class T>
RCPtr2<T>::~RCPtr2()
{
    if (pointee)pointee->removeReference();
}
template<class T>
RCPtr2<T>& RCPtr2<T>::operator=(const RCPtr2& rhs)
{
    if (pointee != rhs.pointee) {
        if (pointee) pointee->removeReference();
        pointee = rhs.pointee;
        init();
    }
    return *this;
}
template<class T>
T* RCPtr2<T>::operator->() const
{
    return pointee;
}
template<class T>
T& RCPtr2<T>::operator*() const
{
    return *pointee;
}


void RString2::StringValue::init(const char *initValue)
{
    data = new char[strlen(initValue) + 1];
    strcpy(data, initValue);
}
RString2::StringValue::StringValue(const char *initValue)
{
    init(initValue);
}
RString2::StringValue::StringValue(const StringValue& rhs)
{
    init(rhs.data);
}
RString2::StringValue::~StringValue()
{
    delete [] data;
}
RString2::RString2(const char *initValue)
        : value(new StringValue(initValue)) {}
const char& RString2::operator[](int index) const
{
    return value->data[index];
}
char& RString2::operator[](int index)
{
    if (value->isShared()) {
        value = new StringValue(value->data);
    }
    value->markUnshareable();
    return value->data[index];
}


//////////////////////proxyclass.cpp///////////////////////////////////////////

const RString3::CharProxy RString3::operator[](int index) const
{
    return CharProxy(const_cast<RString3&>(*this), index);
}
RString3::CharProxy RString3::operator[](int index)
{
    return CharProxy(*this, index);
}
RString3::CharProxy::CharProxy(RString3& str, int index)
        : theString(str), charIndex(index) {}
RString3::CharProxy::operator char() const
{
    return theString.value->data[charIndex];
}
RString3::CharProxy&
RString3::CharProxy::operator=(const CharProxy& rhs)
{
    // if the string is sharing a value with other RString3 objects,
    // break off a separate copy of the value for this string only
    if (theString.value->isShared()) {
        theString.value = new StringValue(theString.value->data);
    }
    // now make the assignment: assign the value of the char
    // represented by rhs to the char represented by *this
    theString.value->data[charIndex] =
        rhs.theString.value->data[rhs.charIndex];
    return *this;
}
RString3::CharProxy& RString3::CharProxy::operator=(char c)
{
    if (theString.value->isShared()) {
        theString.value = new StringValue(theString.value->data);
    }
    theString.value->data[charIndex] = c;
    return *this;
}
const char * RString3::CharProxy::operator&() const
{
    return &(theString.value->data[charIndex]);
}
char * RString3::CharProxy::operator&()
{
    // make sure the character to which this function returns
    // a pointer isn't shared by any other RString3 objects
    if (theString.value->isShared()) {
        theString.value = new StringValue(theString.value->data);
    }
    // we don't know how long the pointer this function
    // returns will be kept by clients, so the StringValue
    // object can never be shared
    theString.value->markUnshareable();
    return &(theString.value->data[charIndex]);
}


void RString3::StringValue::init(const char *initValue)
{
    data = new char[strlen(initValue) + 1];
    strcpy(data, initValue);
}
RString3::StringValue::StringValue(const char *initValue)
{
    init(initValue);
}
RString3::StringValue::StringValue(const StringValue& rhs)
{
    init(rhs.data);
}
RString3::StringValue::~StringValue()
{
    delete [] data;
}
//////////////////////proxyclass.cpp///////////////////////////////////////////
