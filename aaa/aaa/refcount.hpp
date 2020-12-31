#ifndef _REFCOUNT_
#define _REFCOUNT_
#include<cstring>
class RCObject
{
public:
    RCObject();
    RCObject(const RCObject& rhs);
    RCObject& operator=(const RCObject& rhs);
    virtual ~RCObject() = 0;
    void addReference();
    void removeReference();
    void markUnshareable();
    bool isShareable() const;
    bool isShared() const;
private:
    int refCount;
    bool shareable;
};

// template class for smart pointers-to-T objects. 
// T must support the RCObject interface, 
// typically by inheriting from RCObject
template<class T>
class RCPtr
{
public:
    RCPtr(T* realPtr = 0);
    RCPtr(const RCPtr& rhs);
    ~RCPtr();
    RCPtr& operator=(const RCPtr& rhs);
    T* operator->() const;            // see Item 28
    T& operator*() const;             // see Item 28
private:
    T *pointee;                       // dumb pointer this
    // object is emulating
    void init();                      // common initialization
};

class RString
{
private:
    struct StringValue: public RCObject {
        char *data;
        StringValue(const char *initValue);
        StringValue(const StringValue& rhs);
        ~StringValue();
    };
    StringValue *value;                // value of this RString
    ////...
};
#endif /* _REFCOUNT_ */