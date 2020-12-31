#pragma  once
#include <iostream>
#include <utility>   // for pair and make_pair()
using namespace std;

template <typename T>
struct MemFuncTraits { };
template <typename R, typename O>
struct MemFuncTraits<R (O::*)()> {
    typedef R ReturnType;
    typedef O ObjectType;
};
template <typename R, typename O>
struct MemFuncTraits<R (O::*)() const> {
    typedef R ReturnType;
    typedef O ObjectType;
};
template <typename R, typename O, typename P1>
struct MemFuncTraits<R (O::*)(P1)> {
    typedef R ReturnType;
    typedef O ObjectType;
};
template <typename R, typename O, typename P1>
struct MemFuncTraits<R (O::*)(P1) const> {
    typedef R ReturnType;
    typedef O ObjectType;
};
template <typename MemFuncPtrType>
class PMFC3
{
public:
    typedef typename MemFuncTraits<MemFuncPtrType>::ObjectType ObjectType;
    typedef typename MemFuncTraits<MemFuncPtrType>::ReturnType ReturnType;
    typedef std::pair<ObjectType*, MemFuncPtrType> CallInfo;
    PMFC3(const CallInfo& info) : _callinfo(info) { }
    // support for 0 parameter
    ReturnType operator()() const {
        return (_callinfo.first->*_callinfo.second)();
    }
    // support for 1 parameter
    template <typename Param1Type>
    ReturnType operator()(Param1Type p1) const {
        return (_callinfo.first->*_callinfo.second)(p1);
    }
private:
    CallInfo _callinfo;
};

//template <typename MemFuncPtrType>
//const PMFC<MemFuncPtrType>
//operator->*(MemFuncPtrType pmf) const
//{
//    return std::make_pair(ptr, pmf);
//}

template <typename T>
class SmartPtrBase3
{
public:
    SmartPtrBase3(T *p) : ptr(p) { }
    template <typename MemFuncPtrType>
    const PMFC3<MemFuncPtrType> operator->*(MemFuncPtrType pmf) const {
        return std::make_pair(ptr, pmf);
    }
private:
    T* ptr;  // dumb pointer
};
template <typename T>
class SP3 : private SmartPtrBase3<T>
{
public:
    SP3(T *p) : SmartPtrBase3<T>(p) { }
    using SmartPtrBase3<T>::operator->*;
    // normal smart pointer functions would go here.
};

void testMFP();