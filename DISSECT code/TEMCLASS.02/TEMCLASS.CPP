#include <iostream.h>

template <class T>
class CThree
{
public :
    CThree(T t1, T t2, T t3);
    T Min();
    T Max();

private:
    T a, b, c;
};

template <class T>
T CThree<T>::Min()
{
    T minab = a < b ? a : b;
    return minab < c ? minab : c;
}

template <class T>
T CThree<T>::Max()
{
    T maxab = a < b ? b : a;
    return maxab < c ? c : maxab;
}

template <class T>
CThree<T>::CThree(T t1, T t2, T t3) :
    a(t1), b(t2), c(t3)
{
    return;
}
//---------------------------------------
void main()
{
    CThree<int> obj1(2, 5, 4);
    cout << obj1.Min() << endl;
    cout << obj1.Max() << endl;

    CThree<float> obj2(8.52, -6.75, 4.54);
    cout << obj2.Min() << endl;
    cout << obj2.Max() << endl;

    CThree<long> obj3(646600L, 437847L, 364873L);
    cout << obj3.Min() << endl;
    cout << obj3.Max() << endl;
}
