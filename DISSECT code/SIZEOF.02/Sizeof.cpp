#include <iostream.h>
#include <stdio.h>

class ClassA
{
public:
int m_data1;
int m_data2;
void func1() {   }
void func2() {   }
virtual void vfunc1() {     }
virtual void vfunc2() {     }
};

class ClassB : public ClassA
{
public:
int m_data3;
void func2() {  }
virtual void vfunc1() {   }
};

class ClassC : public ClassB
{
public:
int m_data1;
int m_data4;
void func2() {  }
virtual void vfunc1() {    }
};

void main()
{
  cout << sizeof(ClassA) << endl;
  cout << sizeof(ClassB) << endl;
  cout << sizeof(ClassC) << endl;

  ClassA a;
  ClassB b;
  ClassC c;

  b.m_data1 = 1;
  b.m_data2 = 2;
  b.m_data3 = 3;
  c.m_data1 = 11;
  c.m_data2 = 22;
  c.m_data3 = 33;
  c.m_data4 = 44;
  c.ClassA::m_data1 = 111;

  cout << b.m_data1 << endl;
  cout << b.m_data2 << endl;
  cout << b.m_data3 << endl;
  cout << c.m_data1 << endl;
  cout << c.m_data2 << endl;
  cout << c.m_data3 << endl;
  cout << c.m_data4 << endl;
  cout << c.ClassA::m_data1 << endl;

  cout << &b << endl;
  cout << &(b.m_data1) << endl;
  cout << &(b.m_data2) << endl;
  cout << &(b.m_data3) << endl;
  cout << &c << endl;
  cout << &(c.m_data1) << endl;
  cout << &(c.m_data2) << endl;
  cout << &(c.m_data3) << endl;
  cout << &(c.m_data4) << endl;
  cout << &(c.ClassA::m_data1) << endl;

  ClassB* pb = new ClassB;
  ClassC* pc = new ClassC;

  pb->m_data1 = 1111;
  pc->m_data3 = 3333;

  cout << (int)*((char*)pb+4) << endl;
  cout << (int)*((char*)pc+12) << endl;
}

