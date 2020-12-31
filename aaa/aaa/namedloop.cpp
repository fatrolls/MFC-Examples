#include <iostream>
#include <string>
#include "functions.hpp"

#define named(blockname) goto blockname; \
                         blockname##_skip: if (0) \
                         blockname:

#define breaked(blockname) goto blockname##_skip;

 
struct test
{
   std::string str;
   test (std::string s) : str(s) { 
      std::cout << "test::test()::" << str << "\n"; 
   }
   ~test () { 
      std::cout << "~test::" << str << "\n"; 
   }
};

int namedloop(void)
{
   named (outer) 
      for (int i = 0; i < 10; i++)
      {
         test t1("t1");
         int j = 0;
         named(inner)
            for (test t2("t2"); j < 5; j++)
            {
               test t3("t3");
               if (j == 1) breaked(outer);
               if (j == 3) breaked(inner);
               test t4("t4");
            }
            std::cout << "after inner\n";
      }
      return 0;
}

