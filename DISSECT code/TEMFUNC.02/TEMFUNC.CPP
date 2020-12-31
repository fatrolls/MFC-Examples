#include <iostream.h>

template <class T>
T power(T base, int exponent)
{
    T result = base;
    if (exponent == 0)  return (T)1;
    if (exponent < 0)   return (T)0;
    while (--exponent)  result *= base;
    return result;
}

void main()
{
    int i = power(5, 4);
    long l = power(1000L, 3);
    long double d = power((long double)1e5, 2);

    cout << "i= " << i << endl;
    cout << "l= " << l << endl;
    cout << "d= " << d << endl;
}
