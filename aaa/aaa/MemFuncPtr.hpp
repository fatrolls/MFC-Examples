#pragma  once
#include <iostream>
#include <utility>   // for pair and make_pair()
template<typename ObjectType,         
typename ReturnType,         
typename MemFuncPtrType>     
class PMFC
{
public:
    typedef std::pair<ObjectType*, MemFuncPtrType> CallInfo;
    PMFC(const CallInfo& info): callInfo(info) {}
    ReturnType operator()() const {
        return (callInfo.first->*callInfo.second)();
    }
    template<typename Param1Type>
    ReturnType operator()(Param1Type p1) const {
        return (callInfo.first->*callInfo.second)(p1);
    }
private:
    CallInfo callInfo;
};

template <typename T>
class SP
{
public:
    SP(T *p): ptr(p) {}
    template <typename ReturnType>
    const PMFC<T, ReturnType, ReturnType (T::*)() const>
    operator->*(ReturnType (T::*pmf)() const) const {
        return std::make_pair(ptr, pmf);
    }
    template <typename ReturnType>
    const PMFC<T, ReturnType, ReturnType (T::*)()>
    operator->*(ReturnType (T::*pmf)()) const {
        return std::make_pair(ptr, pmf);
    }
    template <typename ReturnType, typename Param1Type>
    const PMFC<T, ReturnType, ReturnType (T::*)(Param1Type)>
    operator->*(ReturnType (T::*pmf)(Param1Type)) const {
        return std::make_pair(ptr, pmf);
    }
    ////...
private:
    T* ptr;
};

//////////////////////////////

template <typename T>   
class SmartPtrBase2      // ¶Ô operator->* µÄÖ§Ô®¡£
{
public:
   SmartPtrBase2(T *initVal): ptr(initVal) {}

   template <typename ReturnType>
   const PMFC<T, ReturnType, ReturnType (T::*)()>
      operator->*(ReturnType (T::*pmf)()) const {
         return std::make_pair(ptr, pmf);
   }

   template <typename ReturnType, typename Param1Type>
   const PMFC<T, ReturnType, ReturnType (T::*)(Param1Type)>
      operator->*(ReturnType (T::*pmf)(Param1Type)) const {
         return std::make_pair(ptr, pmf);
   }
   ////...
protected:
   T* ptr;
};
template <typename T>
class SP2: private SmartPtrBase2<T>
{
public:
   SP2(T *p ): SmartPtrBase2<T>(p) {}
   using SmartPtrBase2<T>::operator->*;    // ÈÃ¡¸private ¼Ì³Ð¶øÀ´µÄ
   // operator->* templates¡¹ ³ÉÎª public¡£
   // ÖÇÄÜÖ¸±êµÄÒ»°ãº¯Ê½·ÅÔÚÕâ¶ù¡£operator->* »úÄÜÔòÊÇ½åÓÉ¼Ì³Ð»úÖÆ»ñµÃ¡£
};

