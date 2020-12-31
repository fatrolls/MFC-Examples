#include <iostream.h>
#include <string.h>

class CDemo
{
public:
       CDemo(const char* str);
       ~CDemo();
private:
       char name[20];
};

CDemo::CDemo(const char* str)
{
  strncpy(name, str, 20);
  cout << "Constructor called for " << name << '\n';
}

CDemo::~CDemo()
{
  cout << "Destructor called for " << name << '\n';
}

void func()
{
  CDemo LocalObjectInFunc("LocalObjectInFunc");  // in stack
  static CDemo StaticObject("StaticObject");     // local static
  CDemo* pHeapObjectInFunc = new CDemo("HeapObjectInFunc"); // in heap

  cout << "Inside func" << endl;

}

CDemo GlobalObject("GlobalObject");  // global static

void main()
{
  CDemo LocalObjectInMain("LocalObjectInMain"); // in stack
  CDemo* pHeapObjectInMain = new CDemo("HeapObjectInMain"); // in heap

  cout << "In main, before calling func\n";
  func();
  cout << "In main, after calling func\n";

}
