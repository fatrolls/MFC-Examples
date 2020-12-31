#include "abc.hpp"
#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#define MACRO(arg1, arg2) do {  \
   /* declarations, if any */    \
   arg1+=1;                   \
   arg2+=2;                   \
   /* ... */                     \
  } while(0)    /* (no trailing ; ) */
//using namespace std;
void testABC() 
{ 
    C c; 
    c.f(); 
    c.C::f(); 
} 

void ucopy()
{
    int A1[] = {1, 2, 3, 4, 5, 6, 7};
    const int N = sizeof(A1) / sizeof(int);

    Int* A2 = (Int*) malloc(N * sizeof(Int));
    std::uninitialized_copy(A1, A1 + N, A2);
    std::vector<int> V(15);
    std::fill(V.begin(), V.end(), 1);
    std::copy_backward(V.begin(), V.begin() + 10, V.begin() + 15);
    //////////////////////////////Shrink-to-fit
    std::vector <int> v;
    //... Lots of push_backs and then lots of remove on v.
    std::vector<int>(v).swap (v);
    /////////////////////////////////Clear-and-minimize
    std::vector <int> v2;
    //... Lots of push_backs and then lots of remove on v2.
    std::vector<int>().swap (v2);
    /////////////////////////////////
    int x = 9;
    int y = 1;
    MACRO(x,y);
    //////////////////////////////////
    Directory<int>::type age;    // This is a map.
    Directory<float>::type  num;
#if 0
    std::transform(age.begin(), age.end(),
       std::ostream_iterator<string>(std::cout, "\n"),
       Directory<int>::KeySelector());
#endif
}

int valref( )
{
    typedef std::allocator<int> alloc1;
    typedef std::allocator<int> alloc2;

    std::vector<int> a(10, 1);
    for (int i = 0; i < 10; a.push_back(i++));
    std::vector<int> b(5, 4);

    std::vector<int>::iterator it1 = find(a.begin(), a.end(), b[1]);
    std::vector<int>::iterator it2 = find(a.begin(), a.end(), b[1]);

    std::cout<<"\t"<<"\t"<<"\t"<<"\t"<<"\t";
    std::cout<<*it1<<"\t"<<*it2<<"\t";
    return 0;
}

std::ostream & operator << (std::ostream & o, X const & x)
{
   o << x.a << " " << x.b;
   return o;
}

void namedparams (void)
{
   // The following code uses the named parameter idiom.
   std::cout << X::create().setA(10).setB('Z') << std::endl;
}
//////////////////////////////////////
#include "final1.hpp"
void finalclass (void)
{
   Test t; // Compilation error here.//??????
}

///////////////////////////
struct File
{
   int read_line (std::string str){
      std::cout<<str.c_str();
      return str.size();
   }
};

void read_lines(std::vector<File *> files)
{
   typedef std::mem_fun1_t<int, File, std::string> Wrapper;  
   std::string arg;
   for_each(files.begin(), files.end(),
      std::binder2nd<Wrapper>(Wrapper(&File::read_line), arg));//----------

   for_each(files.begin(), files.end(), bind2nd(mem_fun(&File::read_line), arg));
}
//////////////////////////////////////
#include "nocopyable.hpp"

#if 0
NoImplicitCopy foocopy()   // Compiler error because copy-constructor must be invoked implicitly to return by value.  
{
   NoImplicitCopy n;
   return n;
}
void bar(NoImplicitCopy n)   // Compiler error because copy-constructor must be invoked implicitly to pass by value.
{
}
#endif

void NoCopy(void)
{
   NoImplicitCopy n;
   NoImplicitCopy x(n);       // This is fine. explicit copy.
#if 0
   n = foocopy();
   bar(n);
#endif
}

void foodel ()
{
   X * p = new X;
   AutoDelete<X> safe_del(p); // Memory will not leak
   if (1==1)
      if (1==2)
         return; 

   // No need to call delete here.
   // Destructor of safe_del will delete memory
}

void foobar(ReaderWriterLock& l)
{
   ScopedLock safe_lock(l); // Lock will be released certainly
   if (1==0)
      if (1==1)
         throw "ERROR"; 
   // No need to call release here.
   // Destructor of safe_lock will release the lock
}

void some_init_function ()
{
   ScopeGuard guard;
   // ...... Something may throw here. If it does we release resources.
   guard.release (); // Resources will not be released in normal execution.
}

///////////////////////////Resource Return
struct Xpro
{
   void foo() {}
};
std::auto_ptr<Xpro> Xfactory() // Resource ownership explicitly transferred to the caller.
{
   return std::auto_ptr<Xpro> (new Xpro); // Dynamically allocated instance
}
//shared_ptr
//unique_ptr
void resourcereturn (void)
{
   Xfactory()->foo(); // Dynamically allocated instance of X does not leak here
}

///////////////////////////////////Return Type Resolver
class getRandomN 
{
   size_t count;

public:
   getRandomN(int n = 5) : count(n) {}

   template <class Container>
   operator Container () {
      Container c;
      for(size_t i = 0;i < count; ++i)
         c.insert(c.end(), rand());
      return c;
   }
};

void returntype()
{
   std::set<int> random_s = getRandomN(10);
   std::vector<int> random_v = getRandomN(10);
   std::list<int> random_l = getRandomN(10);
}