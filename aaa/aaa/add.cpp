#include "add.hpp"
template <typename P1, typename P2> 
AddT<P1, P2> add(P1 x, P2 y)
{
    return AddT<P1, P2>(x,y);
}

void testAddT()
{
    (int)add(3.0, 2);

    float a=1.0;
    float b=2.0;
    (int)add(a,b);

}
