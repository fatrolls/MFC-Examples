#pragma  once
#include <iostream>
#include <string> 
using namespace std;
class String3{
public:
    String3(){    a=NULL;length=0;}
    String3(const char *a1,int ln){
        a=new char[ln];
        length=ln;
        for (int i=0;i<ln;i++)
        {
            a[i]=a1[i];
        }
    }
    String3(const char *a1){
        int ln=0;
        while (a1[ln]!=0)
            ++ln;
        if (ln==0)
        {
            return;
        }
        a=new char[ln];
        length=ln;
        for (int i=0;i<ln;i++)
        {
            a[i]=a1[i];
        }
    }
    ~String3(){
        if (a!=NULL)
        {    
            delete [] a;
            a=NULL;
            length=0;
        }
    }
    String3& operator=(const String3& lstr)
    {
        if (a!=NULL)
            delete [] a;
        length=lstr.length;
        a=new char[length];

        for (int i=0;i<length;i++)
        {
            a[i]=lstr.a[i];
        }
    }
    String3(const String3 &my1){
        //a=my1.a;

        length=my1.length;
        a=new char[length];

        for (int i=0;i<length;i++)
        {
            a[i]=my1.a[i];
        }
    }
    const int getLength()const
    {
        return length;
    }
    char *my_string(){
        return a;
    }
    friend String3 stringcat(const String3& lstr, const String3& rstr);
    friend ostream& operator <<(ostream& os, const String3& lstr);
private:
    char *a;
    int length;
};
String3 stringcat(const String3& lstr, const String3& rstr);
ostream& operator <<(ostream& os, const String3& lstr);
int testmystr();

///////////////////////////
class StringX{
public:
   StringX(){
      a=NULL;
      length=0;
   }
   StringX(const char *a1,int len){
      a=new char[len+1];
      length=len;
      for (int i=0;i<len;i++)
      {
         a[i]=a1[i];
      }
      a[len]=0;
   }
   StringX(const StringX &my1){
      //a=my1.a;

      length=my1.length;
      a=new char[length+1];

      for (int i=0;i<length;i++)
      {
         a[i]=my1.a[i];
      }
      a[length]=0;
   }
   ~StringX(){
      if (a!=NULL)
      { 
         delete [] a;
         a=NULL;
         length=0;
      }
   }
   char* my_string(){
      return a;
   }
   const int getLength()const
   {
      return length;
   }

   void printmem() const
   {
      cout<<(&StringX::a)<<endl;
      cout<<(&StringX::length)<<endl;
      cout<<(&StringX::d)<<endl;
      cout<<(&StringX::e)<<endl;
      printf("String3\n");
      printf("%p\n",&StringX::a);
      printf("%p\n",&StringX::length);
      printf("%p\n",&StringX::d);
      printf("%p\n",&StringX::e);

      char* StringX::* p1=0;
      char* StringX::* p2=&StringX::a;
      if (p1==p2)
      {
         cout<<"they are same!";
      }
   }

   //private:
   char *a;
   int length;
   float d;
   float e;
};
class StringY{
public:
   void printmem() const
   {
      printf("yourstring\n");
      printf("%p\n",&StringY::t);
      printf("%p\n",&StringY::v);
   }
   //private:
   float t;
   float v;
};
class StringZ : public StringX, StringY{
public:
   void printmem() const
   {
      printf("hisstring\n");
      printf("%p\n",&StringZ::a);
      printf("%p\n",&StringZ::length);
      printf("%p\n",&StringZ::d);
      printf("%p\n",&StringZ::e);
      printf("%p\n",&StringZ::t);
      printf("%p\n",&StringZ::v);
      printf("%p\n",&StringZ::w);
      printf("%p\n",&StringZ::z);
   }
   //private:
   float w;
   float z;
};
int teststrxyz();
