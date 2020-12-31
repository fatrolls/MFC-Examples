#pragma  once
#include<cstring>
class RCObject2                         // base class for reference-counted objects
{
public:                                
    void addReference();
    void removeReference();
    void markUnshareable();
    bool isShareable() const;
    bool isShared() const;
protected:
    RCObject2();
    RCObject2(const RCObject2& rhs);
    RCObject2& operator=(const RCObject2& rhs);
    virtual ~RCObject2() = 0;
private:
    int refCount;
    bool shareable;
};




template<class T>                       // template class for smart pointers-to-T objects; 
class RCPtr2                            //T must inherit from RCObject2
{
public:                                
    RCPtr2(T* realPtr = 0);
    RCPtr2(const RCPtr2& rhs);
    ~RCPtr2();
    RCPtr2& operator=(const RCPtr2& rhs);
    T* operator->() const;
    T& operator*() const;
private:
    T *pointee;
    void init();
};

class RString2                             // class to be used by application developers
{
public:                                  
    RString2(const char *value = "");
    const char& operator[](int index) const;
    char& operator[](int index);
private:
    // class representing string values
    struct StringValue: public RCObject2 {
        char *data;
        StringValue(const char *initValue);
        StringValue(const StringValue& rhs);
        void init(const char *initValue);
        ~StringValue();
    };
    RCPtr2<StringValue> value;
};
///////////////////////////proxyclass.hpp///////////////////////////
class RString3                     // reference-counted strings;
{
public:                           // see Item 29 for details
    class CharProxy                 // proxies for string chars
    {
    public:
        CharProxy(RString3& str, int index);                // creation
        CharProxy& operator=(const CharProxy& rhs);       // lvalue
        CharProxy& operator=(char c);                     // uses
        operator char() const;                            // rvalue
        // use
        char * operator&();
        const char * operator&() const;
    private:
        RString3& theString;            // string this proxy pertains to
        int charIndex;                // char within that string
        // this proxy stands for
    };
    // continuation of RString3 class
    const CharProxy
    operator[](int index) const;   // for const Strings
    CharProxy operator[](int index); // for non-const Strings
    ////...
    friend class CharProxy;
private:
    struct StringValue: public RCObject2 {
        char *data;
        StringValue(const char *initValue);
        StringValue(const StringValue& rhs);
        void init(const char *initValue);
        ~StringValue();
    };
    RCPtr2<StringValue> value;
};
///////////////////////////proxyclass.hpp///////////////////////////