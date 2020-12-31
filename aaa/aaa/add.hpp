#pragma  once
template <typename P1, typename P2>
class AddT
{
public:
    AddT(const P1& p1, const P2& p2)
        : m_p1(p1), m_p2(p2) {}
    operator P1()
        {return m_p1 + (P1)m_p2;}
    operator P2()
        {return (P2)m_p1 + m_p2;}
private:
    const P1& m_p1;
    const P2& m_p2;
};

template <typename P1> 
class AddT<P1, P1> 
{ 
public: 
    AddT(P1 p1, P1 p2)
        : m_p1(p1), m_p2(p2) {}
    operator P1()
        {return m_p1 + (P1)m_p2;}
private: 
    const P1 &m_p1, &m_p2;
};

template <typename P1, typename P2> 
AddT<P1, P2> add(P1 x, P2 y);
void testAddT();

////////////////////////////////////////Policy Clone
template <typename T>
class NiftyAlloc
{
public:
   template <typename Other>
   struct rebind // The Policy Clone idiom
   { 
      typedef NiftyAlloc <Other> other;
   };
   //...
};

template <typename T, class Alloc = NiftyAlloc <T> >
class VectorCP 
{
public:
   typedef typename Alloc::template rebind<long>::other ClonePolicy;
   // Here, Alloc may not be a template class or a parametrized instantiation of
   // a class that takes unknown number of type parameters.
};