#pragma  once
#include "refcount.hpp"
template<class T>
class RCIPtr
{
public:
    RCIPtr(T* realPtr = 0);
    RCIPtr(const RCIPtr& rhs);
    ~RCIPtr();
    RCIPtr& operator=(const RCIPtr& rhs);
    const T* operator->() const;               // see below for an explanation of why
    T* operator->();                           // these functions are declared this way
    const T& operator*() const;                 
    T& operator*();                            
private:
struct CountHolder: public RCObject {
        ~CountHolder() {
            delete pointee;
        }
        T *pointee;
    };
    CountHolder *counter;
    void init();
    void makeCopy();                                // see below
};


class Widget
{
public:
    Widget(int size);
    Widget(const Widget& rhs);
    ~Widget();
    Widget& operator=(const Widget& rhs);
    void doThis();
    int showThat() const;
};
class RCWidget
{
public:
    RCWidget(int size): value(new Widget(size)) {}
    void doThis() {
        value->doThis();
    }
    int showThat() const {
        return value->showThat();
    }
private:
    RCIPtr<Widget> value;
};
