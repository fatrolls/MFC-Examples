#pragma  once
namespace Private
{
    class NonDerivableHelper2
    {
    protected:
        NonDerivableHelper2(int) {} //ADDED CTOR ARGUMENT
    };
}

#ifdef NDEBUG
#define FINAL_CLASS2
#else
#define FINAL_CLASS2  private virtual Private::NonDerivableHelper2
#endif

class NonDerivable2 : FINAL_CLASS2
{
public:
    NonDerivable2() : NonDerivableHelper2(0) {} //PASS A DUMMY VALUE
};

//class D2 : public NonDerivable2
//{
//    D2() {} //?@AB
//};
//
//class DD2 : public NonDerivable2, FINAL_CLASS2
//{
//    DD2() {} //2KLM
//};

