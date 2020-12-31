#pragma  once
#include <string> 
const                             //  这是一个const对象//...
class {
public:
    template<class T>               //  可以转换任何类型
    operator T*() const           //  的 null非成员指针
    { return 0; }                 //
    template<class C, class T>      //  可以转换任何类型
    operator T C::*() const       //  的 null成员指针
    { return 0; }
private:
    void operator&() const;         //  不能取其地址
                                  // (见条款27)
} NullClass;                           //  名字为 NULL

void f(int x);                    //  和以前一样
void f(std::string *p);                //  同上

void testNull();


#include <typeinfo>

const // It is a const object...
class nullptr_t_ 
{
public:
   template<class T>
   inline operator T*() const // convertible to any type of null non-member pointer...
   { return 0; }

   template<class C, class T>
   inline operator T C::*() const   // or any type of null member pointer...
   { return 0; }

private:
   void operator&() const;  // Can't take address of nullptr

} nullptr_ = {};

struct Cnull
{
   void func();
};

template<typename T> 
void g( T* t ) {}

template<typename T> 
void h( T t ) {}
