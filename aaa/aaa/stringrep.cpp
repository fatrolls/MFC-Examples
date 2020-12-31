#include <cstdio>
#include <algorithm>
namespace { // anonymous namespace
   class StringRep {
      friend class String;
   public:
      StringRep(const char *s): count(1) {
         strcpy(data=new char[strlen(s)+1], s);
      }
      ~StringRep() { delete [] data; }
      int count; char *data;
   };
} // anonymous namespace

class String {
public:
   String():rep(new StringRep("")) { }
   String(const String &s): rep(s.rep) { rep->count++; }
   String &operator=(const String &s){
      String(s).swap(*this); // copy-and-swap idiom
      return *this;
   }
   ~String() { // StringRep deleted only when the last handle goes out of scope.
      if(rep && --rep->count <= 0) delete rep;
   }
   String(const char *s): rep(new StringRep(s)) { }
   void swap (String & s) throw ()  {
      std::swap(this->rep, s.rep);
   }
   //. . . .
private:
   StringRep *rep;
};
int test() 
{
   ::String a = "hello", b = "world";
   a = b;
   return 0;
}