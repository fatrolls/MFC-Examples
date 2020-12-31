#include<iostream>
#include<cmath>
#include<map>
#include<ctime>
#include "randint.hpp"
using std::map;
using std::cout;
using std::endl;

void randint()
{
    Urand rd(10);
    rd.seed(time(0));
    map<int,int> bucket;
    for (int i=0; i<1000000; i++)    {    bucket[rd()]++;    }
    for (int j=0; j<10; j++)    {    cout<<bucket[j]<<endl;    }
    
}
