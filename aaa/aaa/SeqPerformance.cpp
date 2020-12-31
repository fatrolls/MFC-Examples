#include <vector> 
#include <deque> 
#include <list> 
#include <iostream> 
#include <ctime> 
using namespace std; 
 
#define TEST(type, f)  test(type<Count>(), &type<Count>::f) 
 
class Count 
{ 
private: 
        static int cons, des, copy, ass; 
public: 
        static const int max = 100000; 
 
        Count() {++cons;} 
        ~Count() {++des;} 
        Count(const Count&) {++copy;} 
        void operator =(const Count&) {++ass;} 
 
        static void clear() 
                {cons = des = copy = ass = 0;} 
        friend class Report; 
}; 
 
class Report  
{ 
  static Report nr; 
  Report() {} // Private constructor 
 public: 
 ~Report()  
 { 
  cout << "\n-------------------\n" 
    << "Creations: " << Count::cons 
    << "\nCopy-Constructions: " << Count::copy 
    << "\nAssignments: " << Count::ass 
  << endl; 
 } 
}; 
 
int Count::cons=0, Count::des=0, Count::copy=0, Count::ass=0; 
Report Report::nr; 
 
template <class T, class C> 
        void test(T container, C (T::*f)(const typename T::value_type &)) 
{ 
        Count c; 
        clock_t t = clock(); 
        for(int i = 0; i < Count::max; ++i)  (container.*f)(c); 
        cout << "Total time: " << clock() - t << endl; 
} 
 
void seqperform() 
{ 
       test<vector<Count>, void>(vector<Count>(), &vector<Count>::push_back) ;
 //       TEST(vector, push_back);      //≤‚ ‘ vector 
//        TEST(deque, push_back);      //≤‚ ‘ deque 
//        TEST(list, push_back);      //≤‚ ‘ list 
} 
 
