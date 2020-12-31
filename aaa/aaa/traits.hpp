#pragma  once
class RefCounted 
{ 
public: 
    virtual void IncRef() = 0; 
    virtual bool DecRef() = 0; // if you DecRef() to zero 
        // references, the object is destroyed 
        // automatically and DecRef() returns true 
    virtual ~RefCounted() {} 
}; 
class RefWidget 
{ 
public: 
    void AddReference(); 
    int RemoveReference(); // returns the remaining 
        // number of references; it's the client's 
        // responsibility to destroy the object 

}; 


// Example 6: Reference counting traits 
// 
template <class T> 
class RefCountingTraits 
{ 
    static void Refer(T* p) 
    { 
        p->IncRef(); // assume RefCounted interface 
    } 
    static void Unrefer(T* p) 
    { 
        p->DecRef(); // assume RefCounted interface 
    } 
}; 
template <> 
class RefCountingTraits<RefWidget> 
{ 
    static void Refer(RefWidget* p) 
    { 
        p->AddReference(); // use RefWidget interface 
    } 
        static void Unrefer(RefWidget* p) 
    { 
        // use RefWidget interface 
        if (p->RemoveReference() == 0) 
            delete p; 
    } 
}; 

template <class T, class RCTraits = RefCountingTraits<T> > 
class SmartPtr 
{ 
private: 
    //typedef RefCountingTraits<T> RCTraits; 
    T* pointee_; 
public: 
    ~SmartPtr() 
    { 
        RCTraits::Unrefer(pointee_); 
    } 
}; 
class Lock
{};
class Sentry
{
public:
    Sentry(Lock l){}
    Sentry(){}
};

class MtRefCountingTraits 
{ 
    static void Refer(RefWidget* p) 
    { 
        Sentry s(lock_); // serialize access 
        p->AddReference(); 
    } 
        static void Unrefer(RefWidget* p) 
    { 
        Sentry s(lock_); // serialize access 
        if (p->RemoveReference() == 0) 
            delete p; 
    } 
private: 
    static Lock lock_; 
}; 

 