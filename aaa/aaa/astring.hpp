#pragma  once
#include <cstdio>
#include <algorithm>
class String1
{
public:
    String1(const char *str = NULL); // 通用构造函数
    String1(const String1 &another); // 拷贝构造函数
    ~ String1(); // 析构函数
    String1 & operator=(const String1 &rhs); // 赋值函数
private:
    char *m_data; // 用于保存字符串
};

class String2
{
   char * str;
public:
   String2 & operator = (String2 const &s)
   {
      if (this != &s)
         String2(s).swap (*this); // Copy-constructor and non-throwing swap
      // Old resources are released with the destruction of the temporary above
      return *this;
   }

   String2 & operator = (String2 s) // the pass-by-value parameter serves as a temporary
   {
      s.swap (*this); // Non-throwing swap
      return *this;
   }// Old resources released when destructor of s is called.

   void swap (String2 &s) throw () // Also see non-throwing swap idiom
   {
      std::swap(this->str, s.str);
   }
};