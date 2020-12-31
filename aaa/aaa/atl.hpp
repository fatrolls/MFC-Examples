#pragma  once
#include <iostream>
using namespace std;

class BaseA {
public:
    BaseA() {
        cout << "In BaseA" << endl;
        cout << "Virtual Pointer = " << (int*)this << endl;
        cout << "Address of Vtable = " << (int*)*(int*)this << endl;
        cout << "Value at Vtable 1st entry = " << (int*)*((int*)*(int*)this+0) << endl;
        cout << "Value at Vtable 2nd entry = " << (int*)*((int*)*(int*)this+1) << endl;
        cout << endl;
    }
    virtual void f1() = 0;
    virtual void f2() = 0;
};

class  DriveA : public BaseA {//__declspec(novtable) 
public:
    DriveA() {
        cout << "In DriveA" << endl;
        cout << "Virtual Pointer = " << (int*)this << endl;
        cout << "Address of Vtable = " << (int*)*(int*)this << endl;
        cout << "Value at Vtable 1st entry = " << (int*)*((int*)*(int*)this+0) << endl;
        cout << "Value at Vtable 2nd entry = " << (int*)*((int*)*(int*)this+1) << endl;
        cout << endl;


    }
};

class  MostDriveA : public DriveA {//__declspec(novtable)
public:
    MostDriveA() {
        cout << "In MostDriveA" << endl;
        cout << "Virtual Pointer = " << (int*)this << endl;
        cout << "Address of Vtable = " << (int*)*(int*)this << endl;
        cout << "Value at Vtable 1st entry = " << (int*)*((int*)*(int*)this+0) << endl;
        cout << "Value at Vtable 2nd entry = " << (int*)*((int*)*(int*)this+1) << endl;
        cout << endl;
        // 尝试调用第一个虚函数
        typedef void (*Fun)();
        Fun pFun = (Fun)*((int*)*(int*)this+0);
        pFun();//???

    }
    virtual void f1() { cout << "MostDriveA::f1" << endl; }
    virtual void f2() { cout << "MostDriveA::f2" << endl; }
};

class __declspec(novtable) NMostDriveA : public DriveA {
public:
    NMostDriveA() {
        cout << "In NMostDriveA" << endl;
        cout << "Virtual Pointer = " << (int*)this << endl;
        cout << "Address of Vtable = " << (int*)*(int*)this << endl;
        cout << "Value at Vtable 1st entry = " << (int*)*((int*)*(int*)this+0) << endl;
        cout << "Value at Vtable 2nd entry = " << (int*)*((int*)*(int*)this+1) << endl;
        cout << endl;
    }
    virtual void f1() { cout << "NMostDriveA::f1" << endl; }
    virtual void f2() { cout << "NMostDriveA::f2" << endl; }
};
int testatl( ) ;
//In BaseA
//Virtual Pointer = 0013FF6C
//Address of Vtable = 004031E4
//Value at Vtable 1st entry = 00401F80
//Value at Vtable 2nd entry = 00401F80
//
//In DriveA
//Virtual Pointer = 0013FF6C
//Address of Vtable = 004031FC
//Value at Vtable 1st entry = 00401F80
//Value at Vtable 2nd entry = 00401F80
//
//In MostDriveA
//Virtual Pointer = 0013FF6C
//Address of Vtable = 00403218
//Value at Vtable 1st entry = 00401640
//Value at Vtable 2nd entry = 00401670
//
//MostDriveA::f1
///////////////////////
//In BaseA
//Virtual Pointer = 0013FF68
//Address of Vtable = 004031E4
//Value at Vtable 1st entry = 00401F80
//Value at Vtable 2nd entry = 00401F80
//
//In DriveA
//Virtual Pointer = 0013FF68
//Address of Vtable = 004031FC
//Value at Vtable 1st entry = 00401F80
//Value at Vtable 2nd entry = 00401F80
//
//In NMostDriveA
//Virtual Pointer = 0013FF68
//Address of Vtable = 004031FC
//Value at Vtable 1st entry = 00401F80
//Value at Vtable 2nd entry = 00401F80

