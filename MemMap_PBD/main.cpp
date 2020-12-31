#include <iostream>
#include <string>
#include "MemMap.h"

// test class
class MyClass
{
  public:
    int  m_nInt;
    char m_cChar;
    char m_sBuff[10];
};

// main function
int main()
{

       
  try {
      
      typedef Joshi::MemMapFilePtr<MyClass> MemMappedClass;
      
      // create a object of wrapper class
      MemMappedClass MemClass("/tmp/mymemmap");
      
      // now use MemClass as pointer of MyClass object.
      // Write  int as pointer
      MemClass->m_nInt = 5;
      // dereference it and write char
      (*MemClass).m_cChar = 'a';
      // write as buff
      strcpy(MemClass->m_sBuff, "12345678");
      
      std::cout << "m_nInt:"  << MemClass->m_nInt  << std::endl;
      std::cout << "m_cChar:" << MemClass->m_cChar << std::endl;
      std::cout << "m_sBuff:" << MemClass->m_sBuff << std::endl;
      
  }catch (Joshi::MemMapFileException &e) {
      std::cout << e.what() << std::endl;
  }
  return 0;
}
