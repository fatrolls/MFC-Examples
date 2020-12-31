#include "consdes.hpp"
Bi Play( Bi b)
{
    return b ;
}
///(1) results:
int testB1(int a ) 
{ 
//constructed by parameter 5
//copy constructor by parameter 5
//destructed
//copy constructor by parameter 5
//copy constructor by parameter 5
//destructed
//
//destructed
//destructed

    Bi t1 = Play(a); 
    Bi t2 = Play(t1); 
    cout<<endl;
    return 0;
}

///(2) results:
int testB2(int b ) 
{ 
//constructed by parameter 5
//copy constructor by parameter 5
//destructed
//constructed by parameter 15
//copy constructor by parameter 15
//destructed
//
//destructed
//destructed
    Bi t1 = Play(5);
    Bi t2 = Play(b);
    cout<<endl;
    return 0;
}


int testC1(void) 
{ 
    CLS obj;
    cout << obj.m_i << endl;//-1227421674
    return 0;
}
