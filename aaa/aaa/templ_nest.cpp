#include  "templ_nest.hpp"
void templnest()
{
   AN<int>   a1(5);
   AN<float> a2(5.4);
   AN<char>  a3('a');

   cout << a1 << a2 << a3 << endl;

//<<5>,<5>>
//<<5.4>,<5.4>>
//<<a>,<a>>
//
}


