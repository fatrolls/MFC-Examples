#pragma  once
#include <iostream>
using namespace std;

//  forward declaration  p834 L-8
template <typename T> class AN;
template <typename T> ostream& operator<< (ostream& os, const AN<T>& a);

//--template <typename T> ostream& operator<< (ostream& os, const typename AN<T>::BN & b);

template <typename T>
class AN
{
 //   <T>  p834 L-6
  friend ostream& operator<< <>(ostream& os, const AN<T>& a);

private:
  class BN   // nested class
  {
  public:
    //--friend class AN<T>;
    friend ostream& operator<<(ostream& os,  const BN & b) 
    {
        os << '<' ;
        os << b._item;
        os << '>' ;

        return os;
    }

    BN (T i) : _item(i) { }
    T _item;
  };

public:
  AN (T i) : _i(i) {
            front = new BN(i);
            back  = new BN(i);
  }
 //   dtor  

private:

  T _i;
  BN* front;
  BN* back;
};

template <typename T>
ostream& operator<< (ostream& os, const AN<T>& a)
{
  os << '<' ;
  os << *(a.front);
  os << ',' ;
  os << *(a.back);
  os << '>' << endl;

  return os;
}
//??????????????????????
template <typename T>
ostream& operator<< (ostream& os, const typename AN<T>::BN & b)
{
  os << '<' ;
  os << b._item;
  os << '>' ;

  return os;
}

void templnest();