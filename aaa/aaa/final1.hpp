#pragma  once
namespace Private{

    class NonDerivableHelper
    {
    protected:
        NonDerivableHelper() {}
        friend class NonDerivable;
    };

}

#ifdef NDEBUG
#define FINAL_CLASS
#else
#define FINAL_CLASS  private virtual Private::NonDerivableHelper
#endif

class NonDerivable : FINAL_CLASS
{
    ////... your code here //...
};

//class D: public NonDerivable
//{
//    D() {} //?@AB
//};

class DD: public NonDerivable, FINAL_CLASS
{
    DD() {} //2KLM
};

////////////////////////////
class MakeFinal
{
   ~MakeFinal() {}  // private by default.
   friend class Sealed;
};

class Sealed : virtual MakeFinal
{ };

class Test : public Sealed
{ };

